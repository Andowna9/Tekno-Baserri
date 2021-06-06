extern "C" {
#include <console_config.h>
#include <std_utils.h>
}

#include "WeatherForecast.h"
#include <curl/curl.h>
#include <QtXml>
#include <iostream>
#include <vector>


WeatherForecast::WeatherForecast() {

    weatherFile.setFileName("weather.xml");
}

WeatherForecast::~WeatherForecast() {

    if (weatherFile.exists()) {

        weatherFile.remove();
    }
}

void WeatherForecast::addLocation(std::string name, int id) {

    // Inserta una pareja al mapa
    // Si la clave ya existe, no produce ningún cambio

    locations.insert({name, id});
}

bool WeatherForecast::chooseLocation() {

    std::cout << "Localidades disponibles:" << std::endl << std::endl;

    std::vector<std::string> locationKeys;

    unsigned int i = 1;

    for (const auto &pair: locations) {

        std::cout <<  i << ". " << pair.first << "." << std::endl;

        locationKeys.push_back(pair.first);

        i++;
    }

    std::cout << std::endl;

    try {

            int i = -1;

            std::cout << "Número: ";
            read_format("%d", &i);

            std::cout << std::endl;

            std::string key = locationKeys.at(i - 1);

            forecastCode = locations[key];

            return true;


        }

     catch (std::out_of_range &oor) {

        printf_c(LIGHT_RED_TXT, "Valor incorrecto. Prueba de nuevo!\n");

        return false;
     }



}

bool WeatherForecast::performRequest() {

    CURL *curl;
    FILE* fp;
    CURLcode res;
    bool success = false;

    // Iniciamos la interfaz síncrona de curl

    curl = curl_easy_init();

    if(curl) {

        fp = fopen(weatherFile.fileName().toStdString().c_str(), "w");

        // Opciones de transferencia

        std::string locationURL = apiURL + std::to_string(forecastCode);

        curl_easy_setopt(curl, CURLOPT_URL, locationURL.c_str()); // URL de descarga (imprescindible)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Deshabilitamos certificados de conexión segura
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirección habilitada
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // Puntero a fichero donde se ecriben los datos -> fwrite como callback por defecto


        res = curl_easy_perform(curl); //  Realiza el proceso de transferencia

        if(res != CURLE_OK) {

            printf_c(LIGHT_RED_TXT, "Error de red al actualizar pronóstico del tiempo!\n");

        }

        else {

            printf_c(LIGHT_GREEN_TXT, "Pronóstico de tiempo recuperado correctamente!\n\n");
            success = true;
        }


        curl_easy_cleanup(curl); //  Finalizamos la sesión

        fclose(fp);

    }

      return success;

}

void WeatherForecast::displayForecast() {

    bool received = performRequest(); // Obtiene la información del tiempo

    if (!received) return;

    // Carga en memoria de contenido del xml

    QDomDocument doc;

    if (!weatherFile.open(QIODevice::ReadOnly)) {

        printf_c(LIGHT_RED_TXT, "Error leyendo fichero de tiempo!\n");
        return;
    }

    QString error_msg;

    if (!doc.setContent(&weatherFile, false, &error_msg)) {

        printf_c(LIGHT_RED_TXT, "Error cargando contenido de xml\n");

        std::cerr << error_msg.toStdString() << std::endl;

        weatherFile.close();

        return;
    }

    weatherFile.close();

    // Lectura del xml

    // Meta-info

    // Measurements

    std::string tempM;
    std::string humidityM;
    std::string windM;
    std::string pressureM;

    QDomElement root = doc.documentElement(); // Elemento raiz del documento
    QDomNode n = root.firstChild();

    bool keepSearching = true;

    while(!n.isNull() && keepSearching) {

        QDomElement e = n.toElement(); // try to convert the node to an element.

        if(!e.isNull()) {

            // Uidades de medida

           if (e.tagName() == "information") {

               QDomNodeList infoNodes = e.childNodes();

               for (int i = 0; i < infoNodes.length(); i++) {

                   QDomElement infoElement = infoNodes.at(i).toElement();
                   std::string mUnit = infoElement.firstChild().toText().data().toStdString();

                   if (infoElement.tagName() == "temperature") {

                       tempM = mUnit;

                   }

                   else if (infoElement.tagName() == "humidity") {

                       humidityM = mUnit;
                   }

                   else if (infoElement.tagName() == "wind") {

                        windM = mUnit;
                   }

                   else if (infoElement.tagName() == "pressure") {

                       pressureM = mUnit;
                   }

                }

           }

            // Datos de localidad

           else if (e.tagName() == "locality") {

                QDomNode localityNode = e.firstChild();
                QString locality = localityNode.firstChild().toText().data();

                std::cout << "Localidad: " << locality.toStdString() << std::endl << std::endl;

           }

           // Pronóstico global del día actual

           else if (e.tagName() == "day1") {

               std::cout << "--Datos del día--" << std::endl << std::endl;

                QDomNodeList dayNodes = e.childNodes();

                for (int i = 0; i < dayNodes.length(); i++) {

                    QDomElement dayElement = dayNodes.at(i).toElement();

                    if (dayElement.tagName() == "date") {

                        QString currentDate = dayElement.firstChild().toText().data();
                        std::cout << "Fecha: " << currentDate.toStdString() << std::endl;

                    }

                    else if (dayElement.tagName() == "temperature_max") {

                        int maxTemp = dayElement.firstChild().toText().data().toInt();
                        std::cout << "Máxima temperatura: " << maxTemp << " " << tempM << std::endl;

                    }

                    else if (dayElement.tagName() == "temperature_min") {

                        int minTemp = dayElement.firstChild().toText().data().toInt();
                        std::cout << "Mínima temperatura: " <<  minTemp << " " << tempM << std::endl;

                    }

                    else if (dayElement.tagName() == "text") {

                        QString desc = dayElement.firstChild().toText().data();
                        std::cout << "Descripción: " << desc.toStdString() << std::endl;

                    }

                    else if (dayElement.tagName() == "humidity") {

                        int humidity = dayElement.firstChild().toText().data().toInt();
                        std::cout << "Humedad: " << humidity << " " << humidityM << std::endl;

                    }
                }

            }

           // Pronóstico en la hora actual

           else if (e.tagName() == "hour_hour") {

               std::cout << std::endl << "--Datos de la hora--" << std::endl << std::endl;

               // Consultamos el primer nodo, que se trata de la hora actual

               QDomNodeList hourNodes = e.firstChild().childNodes();

               for (int i = 0; i < hourNodes.length(); i++) {

                   QDomElement hourElement = hourNodes.at(i).toElement();

                   if (hourElement.tagName() == "hour_data") {

                      QString format = "hh:mm";

                      QTime currentHour = QTime::fromString(hourElement.firstChild().toText().data(), format);
                      QTime nextHour = currentHour.addSecs(3600); // 1 h = 3600 s

                      std::cout << "Intervalo: " << currentHour.toString(format).toStdString() << " - ";
                      std::cout << nextHour.toString(format).toStdString() << std::endl;
                   }

                   else if (hourElement.tagName() == "temperature") {

                       int temp = hourElement.firstChild().toText().data().toInt();
                       std::cout << "Temperatura: " << temp << " " << tempM << std::endl;
                   }

                   else if (hourElement.tagName() == "humidity") {

                       int humidity = hourElement.firstChild().toText().data().toInt();
                       std::cout << "Humedad: " << humidity << " " << humidityM << std::endl;
                   }

                   else if (hourElement.tagName() == "wind") {

                       int wind = hourElement.firstChild().toText().data().toInt();
                       std::cout << "Viento: " << wind << " " << windM;

                       // Si el siguiente nodo contiene información de su dirección, la incluimos

                       QDomElement sibling = hourElement.nextSiblingElement();

                       if (!sibling.isNull() && sibling.tagName() == "wind_direction") {

                           QString windDirection =  sibling.firstChild().toText().data();
                           std::cout << " " << windDirection.toStdString();

                       }

                       std::cout << std::endl;

                   }

                   else if (hourElement.tagName() == "pressure") {

                       int pressure = hourElement.firstChild().toText().data().toInt();
                       std::cout << "Presión atmosférica: " << pressure << " " << pressureM << std::endl;

                   }

               }


               // No nos interesa buscar en más nodos del árbol

               keepSearching = false;

           }


        }

        n = n.nextSibling();
    }

   printf_c(LIGHT_MAGENTA_TXT, "\nTiempo metereológico ofrecido por: www.tutiempo.net\n");


}
