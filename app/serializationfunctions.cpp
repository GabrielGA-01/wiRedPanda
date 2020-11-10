#include "box.h"
#include "editor.h"
#include "globalproperties.h"
#include "graphicelement.h"
#include "qneconnection.h"
#include "serializationfunctions.h"

#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QGraphicsView>
#include <QMessageBox>
#include <stdexcept>
#include <QSaveFile>

bool SerializationFunctions::update( QString &fileName, QString dirName ) {
  double version;
  QRectF rect;
  QList< QGraphicsItem* > itemList;
  QFile file( fileName );
  if( file.open( QFile::ReadOnly ) ) {
    COMMENT( "Started reading box file " << fileName.toStdString( ), 0 );
    QMap< quint64, QNEPort* > map = QMap< quint64, QNEPort* >( );
    QDataStream ds( &file );
    version = loadVersion( ds );
    rect = loadRect( ds, version );
    COMMENT( "Version: " << version, 0 );
    COMMENT( "Element deserialization.", 0 );
    itemList = loadMoveData( dirName, ds, version, map );
    COMMENT( "Finished loading data", 0 );
  }

  QSaveFile fl( fileName );
  COMMENT( "Before saving data", 0 );
  if( fl.open( QFile::WriteOnly ) ) {
    COMMENT( "Start updating box " << fileName.toStdString( ), 0 );
    QDataStream ds( &fl );
    ds << QApplication::applicationName( ) + " " + QString::number( GlobalProperties::version );
    ds << rect;
    COMMENT( "Element serialization.", 0 );
    serialize( itemList, ds );
  }
  if( !fl.commit( ) ) {
    std::cerr << "Could not save file: " + fl.errorString( ).toStdString( ) + "." << std::endl;
    return( false );
  }

  COMMENT( "Finished updating box " << fileName.toStdString( ), 0 );
  return( true );
}

void SerializationFunctions::serialize( const QList< QGraphicsItem* > &items, QDataStream &ds ) {
  for( QGraphicsItem *item: items ) {
    if( item->type( ) == GraphicElement::Type ) {
      GraphicElement *elm = qgraphicsitem_cast< GraphicElement* >( item );
      ds << GraphicElement::Type;
      ds << static_cast< quint64 >( elm->elementType( ) );
      elm->save( ds );
    }
  }
  for( QGraphicsItem *item: items ) {
    if( item->type( ) == QNEConnection::Type ) {
      COMMENT( "Writing Connection.", 0 );
      QNEConnection *conn = qgraphicsitem_cast< QNEConnection* >( item );
      ds << QNEConnection::Type;
      conn->save( ds );
    }
  }
}

QList< QGraphicsItem* > SerializationFunctions::deserialize( QDataStream &ds, double version, QString parentFile, QMap< quint64, QNEPort* > portMap ) {
  QFile fl( "/tmp/data.txt" );
  fl.open( QFile::WriteOnly );
  QDataStream ds_data( &fl );

  QList< QGraphicsItem* > itemList;
  while( !ds.atEnd( ) ) {
    int32_t type;
    ds >> type;
    ds_data << type << "\n";
    COMMENT( "Type: " << type, 0 );
    if( type == GraphicElement::Type ) {
      quint64 elmType;
      ds >> elmType;
      ds_data << elmType << "\n";
      COMMENT( "Building " << ElementFactory::typeToText( static_cast< ElementType >( elmType ) ).toStdString( ) << " element.", 0 );
      GraphicElement *elm = ElementFactory::buildElement( static_cast< ElementType >( elmType ) );

      if( elm ) {
        itemList.append( elm );
        elm->load( ds, portMap, version );
        if( elm->elementType( ) == ElementType::BOX ) {
          COMMENT( "Loading box.", 0 );
          Box *box = qgraphicsitem_cast< Box* >( elm );
          BoxManager::instance( )->loadBox( box, box->getFile( ), parentFile );
        }
        elm->setSelected( true );
      }
      else {
        fl.close( );
        throw( std::runtime_error( ERRORMSG( "Could not build element." ) ) );
      }
    }
    else if( type == QNEConnection::Type ) {
      COMMENT( "Reading Connection.", 0 );
      QNEConnection *conn = ElementFactory::buildConnection( );
      conn->setSelected( true );
      if( !conn->load( ds, portMap ) ) {
        COMMENT( "Deleting connection.", 0 );
        delete conn;
      }
      else {
        itemList.append( conn );
      }
    }
    else {
      qDebug( ) << type;
      fl.close( );
      throw( std::runtime_error( ERRORMSG( "Invalid type. Data is possibly corrupted." ) ) );
    }
  }
  fl.close( );
  return( itemList );
}

double SerializationFunctions::loadVersion( QDataStream &ds ) {
  QString str;
  ds >> str;
  if( !str.startsWith( QApplication::applicationName( ) ) ) {
    throw( std::runtime_error( ERRORMSG( "Invalid file format." ) ) );
  }
  bool ok;
  double version = GlobalProperties::toDouble( str.split( " " ).at( 1 ), &ok );
  if( !ok ) {
    throw( std::runtime_error( ERRORMSG( "Invalid version number." ) ) );
  }
  return( version );
}

QRectF SerializationFunctions::loadRect( QDataStream &ds, double version ) {
  QRectF rect;
  if( version >= 1.4 ) {
    ds >> rect;
  }
  return( rect );
}

QList< QGraphicsItem* > SerializationFunctions::loadMoveData( QString dirName, QDataStream &ds, double version, QMap< quint64, QNEPort* > portMap ) {
  QList< QGraphicsItem* > itemList;
  while( !ds.atEnd( ) ) {
    int type;
    ds >> type;
    COMMENT( "Type: " << type, 0 );
    if( type == GraphicElement::Type ) {
      quint64 elmType;
      ds >> elmType;
      COMMENT( "Building " << ElementFactory::typeToText( static_cast< ElementType >( elmType ) ).toStdString( ) << " element.", 0 );
      GraphicElement *elm = ElementFactory::buildElement( static_cast< ElementType >( elmType ) );
      if( elm ) {
        itemList.append( elm );
        elm->load( ds, portMap, version );
        if( elm->elementType( ) == ElementType::BOX ) {
          Box *box = qgraphicsitem_cast< Box* >( elm );
          QString oldName = box->getFile( );
          QString newName = dirName + "/boxes/" + QFileInfo( oldName ).fileName( );
          box->setFile( newName );
        }
        elm->updateSkinsPath( dirName + "/skins/" );
      }
      else {
        throw( std::runtime_error( ERRORMSG( "Could not build element." ) ) );
      }
    }
    else if( type == QNEConnection::Type ) {
      COMMENT( "Reading Connection.", 0 );
      QNEConnection *conn = ElementFactory::buildConnection( );
      if( !conn->load( ds, portMap ) ) {
        COMMENT( "Deleting connection.", 0 );
        delete conn;
      }
      else {
        itemList.append( conn );
      }
    }
    else {
      qDebug( ) << type;
      throw( std::runtime_error( ERRORMSG( "Invalid type. Data is possibly corrupted." ) ) );
    }
  }
  COMMENT( "Finished loading data.", 0 );
  return( itemList );
}

QList< QGraphicsItem* > SerializationFunctions::load( QDataStream &ds, QString parentFile, Scene *scene ) {
  COMMENT( "Started loading file.", 0 );
  QFile fl( "/tmp/serialize.txt" );
  fl.open( QFile::WriteOnly );
  QDataStream ds_header( &fl );
  QString str;
  ds >> str;
  ds_header << str << "\n";
  if( !str.startsWith( QApplication::applicationName( ) ) ) {
    throw( std::runtime_error( ERRORMSG( "Invalid file format." ) ) );
  }
  bool ok;
  double version = GlobalProperties::toDouble( str.split( " " ).at( 1 ), &ok );
  if( !ok ) {
    throw( std::runtime_error( ERRORMSG( "Invalid version number." ) ) );
  }
  QRectF rect;
  if( version >= 1.4 ) {
    ds >> rect;
    ds_header << rect;
  }
  fl.close( );
  COMMENT( "Header Ok. Version: " << version, 0 );
  QList< QGraphicsItem* > items = deserialize( ds, version, parentFile );
  COMMENT( "Finished reading items.", 0 );
  if( scene ) {
    for( QGraphicsItem *item : items ) {
      scene->addItem( item );
    }
    scene->setSceneRect( scene->itemsBoundingRect( ) );
    if( !scene->views( ).empty( ) ) {
      auto const scene_views = scene->views( );
      QGraphicsView *view = scene_views.first( );
      rect = rect.united( view->rect( ) );
      rect.moveCenter( QPointF( 0, 0 ) );
      scene->setSceneRect( scene->sceneRect( ).united( rect ) );
      view->centerOn( scene->itemsBoundingRect( ).center( ) );
    }
  }
  return( items );
}
