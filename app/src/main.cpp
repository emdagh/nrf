#include <stdio.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#define NUM_LEDS 4

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000
#define SLEEP_OFFSET_MS SLEEP_TIME_MS / NUM_LEDS

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec leds[NUM_LEDS] = {
  GPIO_DT_SPEC_GET(LED0_NODE, gpios),
  GPIO_DT_SPEC_GET(LED1_NODE, gpios),
  GPIO_DT_SPEC_GET(LED3_NODE, gpios),
  GPIO_DT_SPEC_GET(LED2_NODE, gpios)
};

//static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

int main(void) {
  
  int ret;
  //bool led_state[NUM_LEDS] = { false };

  for(auto led: leds) {
    if (!gpio_is_ready_dt(&led)) {
      return 0;
    }
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
      return 0;
    }
  }


  int i = 0;
  while (1) {
      ret = gpio_pin_set_dt(&leds[i], 0);
      ret = gpio_pin_set_dt(&leds[(i + 1) % NUM_LEDS], 1);
      k_msleep(SLEEP_OFFSET_MS);
      i = (i + 1) % NUM_LEDS;
  }
  return 0;
}
