#include <pebble.h>
// Set debug = true to get detailed logging output when user presses any button.
bool debug = false;
static Window *window;
static TextLayer *text_layer;
int stage = 0;
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    if (stage == 4){
    stage = 0;
    text_layer_set_text(text_layer, "Congrat Halation");
    if (debug){APP_LOG(APP_LOG_LEVEL_INFO, "User pressed S and succeded, game ended");}
  }
  else{
    stage = 0;
    text_layer_set_text(text_layer, "Fail.");
    if (debug){APP_LOG(APP_LOG_LEVEL_INFO, "User pressed S and failed, game reset");}
  }
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  //text_layer_set_text(text_layer, "Up");
  if (stage == 0 || stage == 3){
    stage++;
    text_layer_set_text(text_layer, "U");
    if (debug){APP_LOG(APP_LOG_LEVEL_INFO, "User pressed U and succeded");}
    }
  else{
    stage = 0;
    text_layer_set_text(text_layer, "Fail.");
    if (debug){APP_LOG(APP_LOG_LEVEL_INFO, "User pressed U and failed, game reset");}
  }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (stage == 1 || stage == 2){
    stage++;
    text_layer_set_text(text_layer, "D");
    if (debug){APP_LOG(APP_LOG_LEVEL_INFO, "User pressed D and succeded");}
  }
  else{
    stage = 0;
    text_layer_set_text(text_layer, "Fail.");
    if (debug){APP_LOG(APP_LOG_LEVEL_INFO, "User pressed D and failed, game reset");}
  }
}
static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create(GRect(0, 72, bounds.size.w, 20));
  text_layer_set_text(text_layer, "Welcome!");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}