# Documentation Best Practices

This page exists to document best practices when writing documentation for QMK. Following these guidelines will help to keep a consistent tone and style, which will in turn help other people more easily understand QMK.

# Page Opening

Your documentation page should generally start with an H1 heading, followed by a 1 paragrah description of what the user will find on this page. Keep in mind that this heading and paragraph will sit next to the Table of Contents, so keep the heading short and avoid long strings with no whitespace.

Example:

```
# My Page Title

This page covers my super cool feature. You can use this feature to make coffee, squeeze fresh oj, and have an egg mcmuffin and hashbrowns delivered from your local macca's by drone.
```

# Headings

Your page should generally have multiple "H1" headings. Only H1 and H2 headings will included in the Table of Contents, so plan them out appropriately. Excess width should be avoided in H1 and H2 headings to prevent the Table of Contents from getting too wide.

# Styled Hint Blocks

You can have styled hint blocks drawn around text to draw attention to it.

```
{% hint style='info' %}
This uses `hint style='info'`
{% endhint %}
```

### Examples:

{% hint style='info' %}
This uses `hint style='info'`
{% endhint %}

{% hint style='tip' %}
This uses `hint style='tip'`
{% endhint %}

{% hint style='danger' %}
This uses `hint style='danger'`
{% endhint %}

{% hint style='working' %}
This uses `hint style='working'`
{% endhint %}

# Styled Terminal Blocks

You can present styled terminal blocks by including special tokens inside your text block.

```
\`\`\`
**[terminal]
**[prompt foo@joe]**[path ~]**[delimiter  $ ]**[command ./myscript]
Normal output line. Nothing special here...
But...
You can add some colors. What about a warning message?
**[warning [WARNING] The color depends on the theme. Could look normal too]
What about an error message?
**[error [ERROR] This is not the error you are looking for]
\`\`\`
```

### Example

```
**[terminal]
**[prompt foo@joe]**[path ~]**[delimiter  $ ]**[command ./myscript]
Normal output line. Nothing special here...
But...
You can add some colors. What about a warning message?
**[warning [WARNING] The color depends on the theme. Could look normal too]
What about an error message?
**[error [ERROR] This is not the error you are looking for]
```
