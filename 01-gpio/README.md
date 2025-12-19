# 01-gpio

Digital input/output fundamentals for ESP32.

## Exercises

| Exercise | Concepts | Hardware |
|----------|----------|----------|
| [blink](blink/) | Digital output, delay | Built-in LED |
| [button](button/) | Digital input, pull-up resistors | Push button |
| [button-led](button-led/) | Input + output, conditionals | Button + LED |

## Key Concepts

- **GPIO**: General Purpose Input/Output pins
- **Digital output**: HIGH (3.3V) or LOW (0V)
- **Digital input**: Read button/switch state
- **Pull-up resistor**: Prevents floating input (use `INPUT_PULLUP`)
