# Valor FRL TKL Rev2.0

An Alice-esque FRL TKL keyboard PCB.

* Keyboard Maintainer: [Xelus22](https://github.com/Xelus22)
* Hardware Supported: Valor FRL TKL
* Hardware Availability: Custom keyboard group buys

### Important Note
This version uses the pin PA9 which is un-usable with the current ChibiOS. The first column will be disabled if this firmware is compiled normally.
A patch is required locally to use this version. 
Please use this patch:
```diff --git a/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.c b/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.c
index 0f48d1fd0..38aff8554 100644
--- a/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.c
+++ b/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.c
@@ -40,18 +40,18 @@
 
 #if STM32_OTG_STEPPING == 1
 #if defined(BOARD_OTG_NOVBUSSENS)
-#define GCCFG_INIT_VALUE        (GCCFG_NOVBUSSENS | GCCFG_VBUSASEN |        \
-                                 GCCFG_VBUSBSEN | GCCFG_PWRDWN)
+#define GCCFG_INIT_VALUE        (GCCFG_NOVBUSSENS |        \
+                                 GCCFG_PWRDWN)
 #else
-#define GCCFG_INIT_VALUE        (GCCFG_VBUSASEN | GCCFG_VBUSBSEN |          \
+#define GCCFG_INIT_VALUE        (GCCFG_NOVBUSSENS |          \
                                  GCCFG_PWRDWN)
 #endif
 
 #elif STM32_OTG_STEPPING == 2
 #if defined(BOARD_OTG_NOVBUSSENS)
-#define GCCFG_INIT_VALUE        GCCFG_PWRDWN
+#define GCCFG_INIT_VALUE        (GCCFG_NOVBUSSENS | GCCFG_PWRDWN)
 #else
-#define GCCFG_INIT_VALUE        (GCCFG_VBDEN | GCCFG_PWRDWN)
+#define GCCFG_INIT_VALUE        (GCCFG_NOVBUSSENS | GCCFG_VBDEN | GCCFG_PWRDWN)
 #endif
 
 #endif
@@ -815,7 +815,7 @@ void usb_lld_start(USBDriver *usbp) {
     otgp->PCGCCTL = 0;
 
     /* VBUS sensing and transceiver enabled.*/
-    otgp->GOTGCTL = GOTGCTL_BVALOEN | GOTGCTL_BVALOVAL;
+    // otgp->GOTGCTL = GOTGCTL_BVALOEN | GOTGCTL_BVALOVAL;
 
 #if defined(BOARD_OTG2_USES_ULPI)
 #if STM32_USB_USE_OTG1
diff --git a/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.h b/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.h
index 69a5ab603..200b4b91a 100644
--- a/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.h
+++ b/os/hal/ports/STM32/LLD/OTGv1/hal_usb_lld.h
@@ -534,7 +534,7 @@ struct USBDriver {
  * @notapi
  */
 #if (STM32_OTG_STEPPING == 1) || defined(__DOXYGEN__)
-#define usb_lld_connect_bus(usbp) ((usbp)->otg->GCCFG |= GCCFG_VBUSBSEN)
+#define usb_lld_connect_bus(usbp)
 #else
 #define usb_lld_connect_bus(usbp) ((usbp)->otg->DCTL &= ~DCTL_SDIS)
 #endif
@@ -545,7 +545,7 @@ struct USBDriver {
  * @notapi
  */
 #if (STM32_OTG_STEPPING == 1) || defined(__DOXYGEN__)
-#define usb_lld_disconnect_bus(usbp) ((usbp)->otg->GCCFG &= ~GCCFG_VBUSBSEN)
+#define usb_lld_disconnect_bus(usbp)
 #else
 #define usb_lld_disconnect_bus(usbp) ((usbp)->otg->DCTL |= DCTL_SDIS)
 #endif
```

Make example for this keyboard (after setting up your build environment):

    make xelus/valor_frl_tkl/rev2_0:default
    make xelus/valor_frl_tkl/rev2_0:via

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
