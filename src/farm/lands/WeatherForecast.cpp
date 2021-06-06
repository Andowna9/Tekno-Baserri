extern "C" {
#include <console_config.h>
}

#include "WeatherForecast.h"
#include <iostream>
using namespace std;
#include <curl/curl.h>
#include <QtXml>
#include <QXmlStreamReader>
#include <QFile>


WeatherForecast::WeatherForecast() {

}

// TODO Configurar código postal para cambiar de localidad cuando se necesite

void WeatherForecast::update() {

    CURL *curl;
    FILE* fp;
    CURLcode res;

    // Iniciamos la interfaz síncrona de curl

    curl = curl_easy_init();

    if(curl) {

        fp = fopen("weather.xml", "w");

        // Opciones de transferencia

        // http://www.aemet.es/xml/municipios/localidad_01006.xml
        // https://api.tutiempo.net/xml/?lan=es&apid=qCDaqXzqaazvx90&lid=8050
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.tutiempo.net/xml/?lan=es&apid=qCDaqXzqaazvx90&lid=8050"); // URL de descarga (imprescindible)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Deshabilitamos certificados de conexión segura
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirección habilitada
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // Puntero a fichero donde se ecriben los datos -> fwrite como callback por defecto


        res = curl_easy_perform(curl); //  Realiza el proceso de transferencia

        if(res != CURLE_OK) {

            printf_c(LIGHT_RED_TXT, "Error de red al actualizar pronóstico del tiempo!\n");

        }

        else {

            printf_c(LIGHT_GREEN_TXT, "Pronóstico de tiempo actualizado correctamente!\n");
        }


        curl_easy_cleanup(curl); //  Finalizamos la sesión

        fclose(fp);


    }

}

void WeatherForecast::showData() {

    // Carga en memoria de contenido del xml

    QDomDocument doc;

    QFile f("weather.xml");

    if (!f.open(QIODevice::ReadOnly)) {

        cerr << "Error leyendo fichero de tiempo!" << endl;

        return;
    }

    QString error_msg;

    if (!doc.setContent(&f, false, &error_msg)) {

        cerr << "Error cargando contenido de xml" << endl;

        cerr << error_msg.toStdString() << endl;

        f.close();
    }

    f.close();

    // Lectura del xml

    QDomElement root = doc.documentElement();

    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();

    bool keepSearching = true;
    while(!n.isNull() && keepSearching) {
        QDomElement e = n.toElement(); // try to convert the node to an element.

        if(!e.isNull()) {
            //cout << qPrintable(e.tagName()) << Qt::endl; // the node really is an element.
            if (e.tagName() == "locality") {
                QDomNode localityNode = e.firstChild();
                QString locality = localityNode.firstChild().toText().data();
                cout << "Localidad: " << locality.toStdString() << endl;


            } else if (e.tagName() == "day1") {
                cout << "Day 1 localizado" << endl;

                QDomElement dayInfo = e.firstChildElement();
                cout << dayInfo.firstChild().toText().data().toStdString() << endl;

                while(!dayInfo.isNull()) {
                    dayInfo = dayInfo.nextSiblingElement();

                    if (dayInfo.tagName() == "date") {
                        cout << "Fecha: " << dayInfo.firstChild().toText().data().toStdString() << endl;

                    } else if (dayInfo.tagName() == "temperature_max") {
                        cout << "Máxima: " << dayInfo.firstChild().toText().data().toStdString() << endl;

                    } else if (dayInfo.tagName() == "temperature_min") {
                        cout << "Mínima: " << dayInfo.firstChild().toText().data().toStdString() << endl;

                    } else if (dayInfo.tagName() == "text") {
                        cout << "Descripción: " << dayInfo.firstChild().toText().data().toStdString() << endl;

                    } else if (dayInfo.tagName() == "humidity") {
                        cout << "Humedad: " << dayInfo.firstChild().toText().data().toStdString() << endl;

                    }
                }

                keepSearching = false;
            }
        }

        n = n.nextSibling();
    }
}
