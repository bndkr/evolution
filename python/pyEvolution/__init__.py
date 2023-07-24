
from . import _pyEvolution

def setup(enable_3d : bool, width : int, height : int):
    '''
    :param enable_3d: (bool) setup the engine for 3D rendering
    :param width: (uint) width of the window in pixels
    :param height: (uint) height of the window in pixels
    :returns: a glfw window object
    '''
    _pyEvolution._setup(enable_3d, width, height)

