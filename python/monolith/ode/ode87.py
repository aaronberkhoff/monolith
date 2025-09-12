import torch
from typing import Callable, Tuple


class ODE78:
    def __init__(self):
        self.alpha = torch.tensor(
            [
                2 / 27,
                1 / 9,
                1 / 6,
                5 / 12,
                0.5,
                5 / 6,
                1 / 6,
                2 / 3,
                1 / 3,
                1.0,
                0.0,
                1.0,
            ],
            dtype=torch.float64,
        )

        self.beta = torch.tensor(
            [
                [2 / 27] + [0] * 12,
                [1 / 36, 1 / 12] + [0] * 11,
                [1 / 24, 0, 1 / 8] + [0] * 10,
                [5 / 12, 0, -25 / 16, 25 / 16] + [0] * 9,
                [0.05, 0, 0, 0.25, 0.2] + [0] * 8,
                [-25 / 108, 0, 0, 125 / 108, -65 / 27, 125 / 54] + [0] * 7,
                [31 / 300, 0, 0, 0, 61 / 225, -2 / 9, 13 / 900] + [0] * 6,
                [2, 0, 0, -53 / 6, 704 / 45, -107 / 9, 67 / 90, 3] + [0] * 5,
                [
                    -91 / 108,
                    0,
                    0,
                    23 / 108,
                    -976 / 135,
                    311 / 54,
                    -19 / 60,
                    17 / 6,
                    -1 / 12,
                ]
                + [0] * 4,
                [
                    2383 / 4100,
                    0,
                    0,
                    -341 / 164,
                    4496 / 1025,
                    -301 / 82,
                    2133 / 4100,
                    45 / 82,
                    45 / 164,
                    18 / 41,
                ]
                + [0] * 3,
                [3 / 205, 0, 0, 0, 0, -6 / 41, -3 / 205, -3 / 41, 3 / 41, 6 / 41, 0]
                + [0] * 2,
                [
                    -1777 / 4100,
                    0,
                    0,
                    -341 / 164,
                    4496 / 1025,
                    -289 / 82,
                    2193 / 4100,
                    51 / 82,
                    33 / 164,
                    12 / 41,
                    0,
                    1,
                ],
            ],
            dtype=torch.float64,
        )

        self.chi = torch.tensor(
            [
                0,
                0,
                0,
                0,
                0,
                34 / 105,
                9 / 35,
                9 / 35,
                9 / 280,
                9 / 280,
                0,
                41 / 840,
                41 / 840,
            ],
            dtype=torch.float64,
        )
        self.psi = torch.tensor(
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, -1], dtype=torch.float64
        )
        self.pow = 1 / 8

    def integrate(
        self,
        func: Callable[[torch.Tensor, torch.Tensor], torch.Tensor],
        t0: float,
        tfinal: float,
        dtmin: float,
        y0: torch.Tensor,
        tol: float,
    ) -> Tuple[torch.Tensor, torch.Tensor]:

        t = torch.tensor(t0, dtype=torch.float64)
        tf = torch.tensor(tfinal, dtype=torch.float64)
        h = torch.sign(tf - t) * abs(dtmin)
        hmin = abs(dtmin)
        hmax = abs(tf - t)
        y = y0.clone().double().reshape(-1, 1)
        f = y.repeat(1, 13) * 0

        forward = 1 if h.item() > 0 else -1
        tout = [t]
        yout = [y.view(-1).clone()]
        varstep = tol != 0
        tau = tol * max(torch.norm(y, p=float("inf")).item(), 1.0)

        while t * forward < tf * forward:
            if (t + h) * forward > tf * forward:
                h = tf - t

            f[:, 0] = func(t, y).view(-1)
            for j in range(12):
                yint = y + h * torch.matmul(f[:, : j + 1], self.beta[: j + 1, j])
                f[:, j + 1] = func(t + self.alpha[j] * h, yint).view(-1)

            if varstep:
                gamma1 = h * 41 / 840 * torch.matmul(f, self.psi.view(-1, 1))
                delta = torch.norm(gamma1, p=float("inf")).item()
                tau = tol * max(torch.norm(y, p=float("inf")).item(), 1.0)
            else:
                delta = 0

            if not varstep or delta <= tau or abs(h) == hmin:
                t = t + h
                y = y + h * torch.matmul(f, self.chi.view(-1, 1))
                tout.append(t.clone())
                yout.append(y.view(-1).clone())

            if varstep and delta != 0.0:
                h = forward * min(hmax, abs(0.8 * h * (tau / delta) ** self.pow))
                if (t + h) * forward > tf * forward:
                    h = tf - t
                h = forward * max(abs(h), hmin)

        return torch.stack(tout), torch.stack(yout)
