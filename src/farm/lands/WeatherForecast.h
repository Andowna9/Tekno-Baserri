#ifndef WEATHERFORECAST_H
#define WEATHERFORECAST_H

#include <QFile>
#include <string>

class WeatherForecast {

    private:

       std::string apiURL = "https://api.tutiempo.net/xml/?lan=es&apid=qCDaqXzqaazvx90&lid=";
       QFile weatherFile;

       std::map<std::string, int> locations {{"Vitoria-Gasteiz", 8043}, {"Bilbao", 8050 }, {"Donostia-San Sebastián", 4917}};
       int code;

    public:

        WeatherForecast();
        ~WeatherForecast();

        void chooseLocation();
        void update();
        void showData();
};

#endif // WEATHERFORECAST_H
