/* Author: Peter Sovietov */

#ifndef AYUMI_H
#define AYUMI_H

enum {
  TONE_CHANNELS = 3,
  DECIMATOR_FACTOR = 8,
  DECIMATOR_SIZE = 192,
  DC_FILTER_SIZE = 1024
};

struct tone_channel {
  int tone_period;
  int tone_counter;
  int tone;
  int t_off;
  int n_off;
  int e_on;
  int volume;
  double pan_left;
  double pan_right;
};

struct interpolator {
  double c[3];
  double y[4];
};

struct dc_filter {
  double sum;
  double delay[DC_FILTER_SIZE];
};

struct ayumi {
  struct tone_channel channels[TONE_CHANNELS];
  int noise_period;
  int noise_counter;
  int noise;
  int envelope_counter;
  int envelope_period;
  int envelope_shape;
  int envelope_segment;
  int envelope;
  const double* dac_table;
  double step;
  double x;
  struct interpolator interpolator_left;
  struct interpolator interpolator_right;
  double decimator_left[DECIMATOR_SIZE];
  double decimator_right[DECIMATOR_SIZE];
  int dc_index;
  struct dc_filter dc_left;
  struct dc_filter dc_right;
  double left;
  double right;
};

void ayumi_configure(struct ayumi* ay, int is_ym, double clock_rate, int sr);
void ayumi_set_pan(struct ayumi* ay, int index, double pan, int is_eqp);
void ayumi_set_tone(struct ayumi* ay, int index, int period);
void ayumi_set_noise(struct ayumi* ay, int period);
void ayumi_set_mixer(struct ayumi* ay, int index, int t_off, int n_off, int e_on);
void ayumi_set_volume(struct ayumi* ay, int index, int volume);
void ayumi_set_envelope(struct ayumi* ay, int period);
void ayumi_set_envelope_shape(struct ayumi* ay, int shape);
void ayumi_process(struct ayumi* ay);
void ayumi_remove_dc(struct ayumi* ay);

#endif
