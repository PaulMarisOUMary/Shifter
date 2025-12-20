from pathlib import Path
from PIL import Image


def rgb888_to_rgb565(r: int, g: int, b: int) -> int:
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)


def image_to_rgb565_array(image_path: Path) -> tuple[list[int], int, int]:
    image = Image.open(image_path).convert("RGB")
    width, height = image.size
    pixels = image.load()

    if pixels is None:
        raise ValueError(f"Failed to load pixels from image: {image_path}")
    
    rgb565_array = [
        rgb888_to_rgb565(*pixels[x, y])
        for y in range(height)
        for x in range(width)
    ]
    
    return rgb565_array, width, height
