import numpy as np

class AdaGrad:
    '''Represents an AdaGrad optimizer

    Fields:
        eta: learning rate
        epsilon: smoothing term
    '''

    eta: float
    epsilon: float

    def __init__(self, *, eta: float = 0.1, epsilon: float = 1e-8):
        '''Initalizes `eta` and `epsilon` fields'''
        self.eta = eta
        self.epsilon = epsilon

    def optimize(self, oracle, x0: np.ndarray, *,
                 max_iter: int = 100, eps: float = 1e-5) -> np.ndarray:
        '''Optimizes a function specified as `oracle` starting from point `x0`.
        The optimizations stops when `max_iter` iterations were completed or 
        the L2-norm of the gradient at current point is less than `eps`

        Args:
            oracle: function to optimize
            x0: point to start from
            max_iter: maximal number of iterations
            eps: threshold for L2-norm of gradient

        Returns:
            A point at which the optimization stopped
        '''
        x = x0
        g = np.zeros_like(x0)
        for epoch in range(max_iter):
            grad = oracle.gradient(x)
            if np.linalg.norm(grad, 2) <= eps:
                break
            g += grad**2
            x -= self.eta*grad / (self.epsilon + np.sqrt(g))
        return x
