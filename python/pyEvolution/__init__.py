from . import _pyEvolution
from typing import Tuple

Float2 = _pyEvolution.Float2
Float3 = _pyEvolution.Float3
Float4 = _pyEvolution.Float4

Mesh = _pyEvolution.Mesh

Camera = _pyEvolution.Camera

def move_vector(vector: Float3):
    _pyEvolution.move_vector(vector)

def setup(enable_3d: bool, width: int, height: int):
    """ """
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


def get_window_size(window: _pyEvolution.Window) -> Tuple[int, int]:
    """ """
    window_size = _pyEvolution.get_window_size(window)
    return (window_size.width, window_size.height)


def clear_buffer() -> None:
    """ """
    _pyEvolution.clear_buffer()


def swap_buffers(window: _pyEvolution.Window) -> None:
    """ """
    _pyEvolution.swap_buffers(window)
