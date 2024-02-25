# watchy-starfield

starfield watchface for Watchy
* step count
* sunrise/sunset time
* moonphase
![picture](/assets/pic.png)

# settings

* To toggle between Dark Mode/Light Mode, change `#define DARKMODE true` in `Watchy_7_SEG.cpp`
* To toggle between 12-hour/24-hour, change `#define HOUR_12_24 24` in `Watchy_7_SEG.cpp`
* To calculate exact sunrise/sunset time, change `#define LOC 31.00, 121.00, 8` in `Watchy_7_SEG.cpp`, the three data represents latitude, longitude and timezone
* You should also change `#define GMT_OFFSET_SEC 3600 * 8 //New York is UTC -5` in `settings.h` for network timing