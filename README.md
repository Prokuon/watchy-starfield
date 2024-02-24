# Watchy-starfield

Starfield watchface for watchy
* step count
* sunrise/sunset time
* moonphase

![picture](/assets/pic.png)

# Settings

* To toggle between Dark Mode/Light Mode, change `#define DARKMODE true` in `Watchy_7_SEG.cpp`
* To toggle between 12-hour/24-hour, change `#define HOUR_12_24 24` in `Watchy_7_SEG.cpp`
* To calculate exact sunrise/sunset time, change `#define LOC 31.00, 121.00, 8` in `Watchy_7_SEG.cpp`, the three data represents latitude, longitude and timezone
* To set the GMT offset for network timing, change `#define GMT_OFFSET_SEC 3600 * 8 //New York is UTC -5` in `settings.h`

# Credits

* [moonPhase-esp32](https://github.com/CelliesProjects/moonPhase-esp32) 
  Utilized code from this repository to calculate lunar phases
* [Dusk2Dawn](https://github.com/dmkishi/Dusk2Dawn)
  Utilized code from this repository to calculate sunrise and sunset time
