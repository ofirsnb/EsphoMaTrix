#ifndef EHMTX_H

#define EHMTX_H
#include "esphome.h"

#define MAXQUEUE 12
#define MAXICONS 32
#define TICKINTERVAL 1000 // each 100ms

namespace esphome
{

  const Color EHMTX_Ctext = Color(178, 178, 191);
  const Color EHMTX_Cwarn = Color(214, 214, 12);
  const Color EHMTX_Calarm = Color(204, 51, 63);
  const Color EHMTX_ctoday = Color(180, 180, 180);
  const Color EHMTX_cday = Color(60, 60, 60);

  class EHMTX_screen;

  class EHMTX : public PollingComponent
  {
  private:
    uint8_t findfreeslot(uint8_t icon);
    float get_setup_priority() const override { return esphome::setup_priority::LATE; }

  public:
    EHMTX();
    bool showalarm;
    bool showclock;
    bool showscreen;
    EHMTX_screen *slots[MAXQUEUE];
    std::string iconlist;
    display::Animation *icons[MAXICONS];
    void add_icon(display::Animation *icon);
    display::DisplayBuffer *display;
    time::RealTimeClock *clock;
    display::Font *font;
    int8_t fontoffset;
    uint16_t scrollintervall; // ms to between scrollsteps
    uint16_t animintervall;   // ms to next_frame()
    uint16_t clocktime;       // ms display of clock/date 0.5 clock then 0.5 date
    uint16_t screentime;      // ms display of screen
    uint8_t iconcount;        // max iconnumber -1
    uint8_t lifetime;         // how often is a screen displayed
    uint8_t activeslot;       // slot to display
    uint8_t lastslot;         // last displayed slot
    uint8_t pointer;          // last displayed slot
    unsigned long lastscrolltime;
    unsigned long lastanimtime;
    time_t 	 lastclocktime = 0; // starttime clock display
    time_t 	 nextactiontime = 0; // when is the nextscreenchange
    time_t 	 lastalarmtime = 0; // starttime last alarm display
    uint8_t findnextscreen();
    uint8_t countscreens();
    uint8_t findalarm();
    void drawdayofweek();
    void tick();
    void draw();
    void draw1();
    void get_status();
    void set_display(display::DisplayBuffer *disp);
    void set_screentime(uint16_t t);
    void set_fontoffset(int8_t t);
    void set_clocktime(uint16_t t);
    void add_alarm(uint8_t icon, std::string text);
    void add_screen(uint8_t icon, std::string text);
    void del_screen(uint8_t icon);
    void set_clock(time::RealTimeClock *clock);
    void set_font(display::Font *font);
    void set_lifetime(uint8_t duration);
    void set_animintervall(uint16_t intervall);
    void set_scrollintervall(uint16_t intervall);
    void set_icons(display::Animation *ia[]);
    void set_iconcount(uint8_t ic);
    void set_iconlist(std::string il);
    void drawclock();
    void setup();
    void update();
  };

  class EHMTX_screen
  {

  private:
    uint8_t shiftx;
    uint8_t pixels;
    EHMTX *config;

  public:
    bool alarm;
    uint16_t lifetime;
    unsigned long lastscreentime;
    uint8_t icon;
    std::string text;

    EHMTX_screen(EHMTX *config);

    bool active();
    bool isalarm();
    void use();
    void draw();
    void _draw();
    bool isfree();
    bool updateslot(uint8_t _icon);
    void update_screen();
    bool delslot(uint8_t _icon);
    void setText(std::string text, uint8_t icon, uint8_t pixels);
  };

}

#endif