__attribute__ ((weak))
void rgb_matrix_indicators_user(void)
{
    if (IS_HOST_LED_ON(USB_LED_NUM_LOCK))
    {
        rgb_matrix_set_color(7, 0xFF, 0xFF, 0xFF);
    }
}
#endif
