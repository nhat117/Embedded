class Button
{
  private:
    int pin;
    uint16_t state;
  public:
    void begin(int pin) {
      this->pin = pin;
      this->state = 0;

    }
    bool debounce() {
      int tmp = 0;
      if (!(PINC & (1 << this->pin))) {
        tmp = 1;
      }
      this->state = (this->state << 1) | tmp | 0xfe00;
      return (this->state == 0xff00);
    }
};
