from . import _pyEvolution

Float2 = _pyEvolution.Float2
Float3 = _pyEvolution.Float3
Float4 = _pyEvolution.Float4

Camera = _pyEvolution.Camera


def setup(enable_3d: bool, width: int, height: int):
    """
    :param enable_3d: (bool) setup the engine for 3D rendering
    :param width: (uint) width of the window in pixels
    :param height: (uint) height of the window in pixels
    :returns: a glfw window object
    """
    return _pyEvolution.setup(enable_3d, width, height)


def add_programs_from_dir(dir: str) -> None:
    """ """
    _pyEvolution.add_programs_from_dir(dir)


def add_textures_from_dir(dir: str) -> None:
    """ """
    _pyEvolution.add_textures_from_dir(dir)


def create_cube_mesh() -> _pyEvolution.Mesh:
    """ """
    return _pyEvolution.create_cube_mesh()


def create_texture_quad() -> _pyEvolution.Mesh:
    """ """
    return _pyEvolution.create_texture_quad()


def window_should_close(window: _pyEvolution.Window) -> bool:
    """ """
    return _pyEvolution.window_should_close(window)


def poll_events() -> None:
    """ """
    _pyEvolution.poll_events()


def update_viewport(width: int, height: int) -> None:
    """ """
    _pyEvolution.update_viewport(0, 0, width, height)
