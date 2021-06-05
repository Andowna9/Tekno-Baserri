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

        curl_easy_setopt(curl, CURLOPT_URL, "http://www.aemet.es/xml/municipios/localidad_01006.xml"); // URL de descarga (imprescindible)
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

    QString name = root.tagName();

    QString version = root.attribute("version", "None");

    cout << "Tag name: " << name.toStdString() << endl;

    cout << "Version: " << version.toStdString() << endl; */

    QFile f("weather.xml");

    if (!f.open(QIODevice::ReadOnly)) {

        cerr << "Error leyendo fichero de tiempo!" << endl;

        return;
    }

    /*

    QString rawXML =
"<root>"
"	<a>11111</a>"
"	<a><b>test 123</b></a>"
"</root>";


    QXmlStreamReader reader(rawXML);
    QStringView s;

    reader.readNextStartElement();
        s = reader.name();
        if (s!="root") {
            return;
        }

    cout << reader.attributes().length() << endl;

    */


}
