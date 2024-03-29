uint8_t wire1 = 25;
uint8_t wire2 = 33;
uint8_t wire3 = 32;
uint8_t wire4 = 22;
const uint16_t _delay = 50; /* delay in between two steps. minimum delay more the rotational
speed */
void sequence(bool a, bool b, bool c, bool d)
/* four step sequence to stepper motor */
{
digitalWrite(wire1, a);
digitalWrite(wire2, b);
digitalWrite(wire3, c);
digitalWrite(wire4, d);
delay(_delay);
}
void setup()
{
pinMode(wire1, OUTPUT); /* set four wires as output */
pinMode(wire2, OUTPUT);
pinMode(wire3, OUTPUT);
pinMode(wire4, OUTPUT);
}
void loop() /* Rotation in one direction */
{
for(int i = 0; i<12; i++)
{
sequence(HIGH, LOW, LOW, LOW);
sequence(HIGH, HIGH, LOW, LOW);
sequence(LOW, HIGH, LOW, LOW);
sequence(LOW, HIGH, HIGH, LOW);
sequence(LOW, LOW, HIGH, LOW);
sequence(LOW, LOW, HIGH, HIGH);
sequence(LOW, LOW, LOW, HIGH);
sequence(HIGH, LOW, LOW, HIGH);
}
sequence(HIGH, LOW, LOW, LOW);
/* Rotation in opposite direction */
for(int j = 0; j<12; j++)
{
sequence(LOW, LOW, LOW, HIGH);
sequence(LOW, LOW, HIGH, HIGH);
sequence(LOW, LOW, HIGH, LOW);
sequence(LOW, HIGH, HIGH, LOW);
sequence(LOW, HIGH, LOW, LOW);
sequence(HIGH, HIGH, LOW, LOW);
sequence(HIGH, LOW, LOW, LOW);
sequence(HIGH, LOW, LOW, HIGH);
}
sequence(LOW, LOW, LOW, HIGH);
}
