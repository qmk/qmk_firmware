Limitation: As this driver only exports one set of variables, this driver can only be used
            on systems with one single touch input device of this type. To overcome this
            limitation, the global variables have to be converted into arrays. The driverinstance
            variable passed to the _read() function is then used to distinguish between the
            different instances.
