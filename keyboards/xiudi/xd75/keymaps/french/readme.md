# Clavier AZERTY français

![Disposition Clavier](https://i.imgur.com/tH9TVBc.png)


# Configuration du clavier

Ce clavier AZERTY est basé sur le fichier keymap_french.c de correspondance QWERTY - AZERTY.

Ce fichier est composé de trois énumérations (layout français, touches de contrôle, touches multimédias) correspondant aux keycodes sous la forme d'hexa.

Il peut être utilisé pour toute autre configuration de clavier juste en incluant ce fichier dans son propre keymap.c.

La touche de fonction permet elle d'avoir accès aux différentes touches multimédias ainsi qu'au pavé numérique. Mais aussi si le clavier est équipé de led, à différents modes d'éclairage.

# Compilation 

```
make xd75:french:dfu
```
