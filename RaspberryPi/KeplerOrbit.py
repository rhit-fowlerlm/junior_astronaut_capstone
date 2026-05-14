import numpy as np

class KeplerOrbit:
    def __init__(self):
        self.a0 = 1
        self.adot = 1
        self.e0 = 1
        self.edot = 1
        self.I0 = 1
        self.Idot = 1
        self.L0 = 1
        self.Ldot = 1
        self.wbar0 = 1
        self.wbardot = 1
        self.Om0 = 1
        self.Omdot = 1

        self.b = 0
        self.c = 0
        self.s = 0
        self.f = 0

    def set_elements_init(self, arr):
        self.a0 = arr[0]
        self.e0 = arr[1]
        self.I0 = arr[2]
        self.L0 = arr[3]
        self.wbar0 = arr[4]
        self.Om0 = arr[5]

    def set_elements_dot(self, arr):
        self.adot = arr[0]
        self.edot = arr[1]
        self.Idot = arr[2]
        self.Ldot = arr[3]
        self.wbardot = arr[4]
        self.Omdot = arr[5]

    def set_additional_terms(self, arr):
        self.b = arr[0]
        self.c = arr[1]
        self.s = arr[2]
        self.f = arr[3]

    def get_coords(self, T):
        a = self.a0 + self.adot*T
        e = self.e0 + self.edot*T
        I = self.I0 + self.Idot*T
        L = self.L0 + self.Ldot*T
        wbar = self.wbar0 + self.wbardot*T
        Om = self.Om0 + self.Omdot*T

        w = wbar - Om

        M = L - wbar + self.b*T*T + self.c*np.cos(np.deg2rad(self.f*T)) + self.s*np.sin(np.deg2rad(self.f*T))

        E = self.__solve_kepler(M, e)
        xp = a * (np.cos(np.deg2rad(E)) - e)
        yp = a * np.sin(np.deg2rad(E)) * np.sqrt(1 - e*e)

        cos_w = np.cos(np.deg2rad(w))
        sin_w = np.sin(np.deg2rad(w))

        cos_Om = np.cos(np.deg2rad(Om))
        sin_Om = np.sin(np.deg2rad(Om))

        cos_I = np.cos(np.deg2rad(I))
        sin_I = np.sin(np.deg2rad(I))

        x_ecl = (cos_w*cos_Om - sin_w*sin_Om*cos_I) * xp + (-sin_w*cos_Om - cos_w*sin_Om*cos_I) * yp
        y_ecl = (cos_w*sin_Om + sin_w*cos_Om*cos_I) * xp + (-sin_w*sin_Om + cos_w*cos_Om*cos_I) * yp
        z_ecl = (                      sin_w*sin_I) * xp + (                       cos_w*sin_I) * yp

        return x_ecl, y_ecl, z_ecl

    def __solve_kepler(self, M, e):
        es = (180/np.pi) * e
        E = M + es * np.sin(np.deg2rad(M))

        dE = np.inf
        tol = 1e-6
        while np.abs(dE) < tol:
            dM = M - (E - es * np.sin(np.deg2rad(E)))
            dE = dM / (1 - e * np.cos(np.deg2rad(E)))
            E += dE

        return E
        
