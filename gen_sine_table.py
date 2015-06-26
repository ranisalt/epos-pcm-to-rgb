import math

with open("sine_table.h", "w") as f:
    sines = []
    for i in range(-1, 362):
        sines.append(str("%.15f" % math.sin(math.radians(i))))

    f.write("""#ifndef SINE_TABLE_H
#define SINE_TABLE_H

    const double sine_table[] = { %s };

#endif /* SINE_TABLE_H */""" % (", ".join(sines), ))
