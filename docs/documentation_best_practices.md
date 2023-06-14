# Documentation Best Practices

This page exists to document best practices when writing documentation for QMK. Following these guidelines will help to keep a consistent tone and style, which will in turn help other people more easily understand QMK.

# Page Opening

Your documentation page should generally start with an H1 heading, followed by a 1 paragraph description of what the user will find on this page. Keep in mind that this heading and paragraph will sit next to the Table of Contents, so keep the heading short and avoid long strings with no whitespace.

Example:

```
# My Page Title

This page covers my super cool feature. You can use this feature to make coffee, squeeze fresh oj, and have an egg mcmuffin and hashbrowns delivered from your local macca's by drone.
```

# Headings

Your page should generally have multiple "H1" headings. Only H1 and H2 headings will included in the Table of Contents, so plan them out appropriately. Excess width should be avoided in H1 and H2 headings to prevent the Table of Contents from getting too wide.

# Styled Hint Blocks

You can have styled hint blocks drawn around text to draw attention to it.

### Important

```
!> This is important
```

Renders as:

!> This is important

### General Tips

```
?> This is a helpful tip.
```

Renders as:

?> This is a helpful tip.


# Documenting Features

If you create a new feature for QMK, create a documentation page for it. It doesn't have to be very long, a few sentences describing your feature and a table listing any relevant keycodes is enough. Here is a basic template:

```markdown
# My Cool Feature

This page describes my cool feature. You can use my cool feature to make coffee and order cream and sugar to be delivered via drone.

## My Cool Feature Keycodes

|Long Name|Short Name|Description|
|---------|----------|-----------|
|KC_COFFEE||Make Coffee|
|KC_CREAM||Order Cream|
|KC_SUGAR||Order Sugar|
```

Place your documentation into `docs/feature_<my_cool_feature>.md`, and add that file to the appropriate place in `docs/_summary.md`. If you have added any keycodes be sure to add them to `docs/keycodes.md` with a link back to your feature page.
