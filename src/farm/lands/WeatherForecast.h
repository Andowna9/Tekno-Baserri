#ifndef WEATHERFORECAST_H
#define WEATHERFORECAST_H

#include <QFile>
#include <string>

class WeatherForecast {

    private:

       std::string apiURL = "https://api.tutiempo.net/xml/?lan=es&apid=qCDaqXzqaazvx90&lid=";
       QFile weatherFile;

       std::map<std::string, int> locations;
       int forecastCode;

       bool performRequest();

    public:

        WeatherForecast();
        ~WeatherForecast();

        void addLocation(std::string name, int id);

        bool chooseLocation();
        void displayForecast();
};

#endif // WEATHERFORECAST_H
