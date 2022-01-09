class YasuoTime {
  private:
    int hour;
    int minute;
    int second;
    
  public:
    YasuoTime();
    YasuoTime(int second, int minute, int hour);
    ~YasuoTime() {}

    void setHour(int hour) {
      this->hour = hour;
    }
    void setMinute(int minute) {
      this->minute = minute;
    }
    void setSecond(int second) {
      this->second = second;
    }
    int getHour() const {
      return this->hour;
    }
    int getMinute() const {
      return this->minute;
    }
    int getSecond() const {
      return this->second;
    }
    void calculateTime(int currentTime[]);

    void increamentHour() {
      if (this->getHour() == 23) {
        this->setHour(0);
      } else {
        this->setHour(this->getHour() + 1);
      }
    }

    void increamentMinute() {
      if (this->getMinute() == 59) {
        this->setMinute(0);
      } else {
        this->setMinute(this->getMinute() + 1);
      }
    }

    void setTime(int currentTime[]);

    void setTime(int hour, int minute, int second);

};
