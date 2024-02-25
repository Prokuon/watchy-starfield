# watchy-starfield

starfield watchface for Watchy
* step count
* sunrise/sunset time
* moonphase

![picture](/assets/img.png)

# settings

* To toggle between Dark Mode/Light Mode, push back button
* To toggle between 12-hour/24-hour, push up or down button
* To calculate exact sunrise/sunset time, change `#define LOC 31.00, 121.00, 8` in `Watchy_7_SEG.cpp`, the three data represents latitude, longitude and timezone
* To set the GMT offset for network timing, change `#define GMT_OFFSET_SEC 3600 * 8` in `settings.h`

# Credits

* [moonPhase-esp32](https://github.com/CelliesProjects/moonPhase-esp32) 

  Utilized code from this repository to calculate lunar phases

* [Dusk2Dawn](https://github.com/dmkishi/Dusk2Dawn)

  Utilized code from this repository to calculate sunrise and sunset time
