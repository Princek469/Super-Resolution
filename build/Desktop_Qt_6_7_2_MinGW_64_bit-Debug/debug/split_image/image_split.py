import os
import rasterio
import sys
import warnings

# Suppress warnings for non-georeferenced images
warnings.filterwarnings("ignore", category=rasterio.errors.NotGeoreferencedWarning)

def split_image(input_image_path, tile_size, output_path, output_format):
    try:
        # Ensure output path exists
        if not os.path.exists(output_path):
            os.makedirs(output_path)

        with rasterio.open(input_image_path) as src:
            # Original image dimensions
            orig_width, orig_height = src.width, src.height
            print(f"Original Image dimensions: {orig_width}x{orig_height}")

            # Calculate the number of tiles in x and y directions
            n_tiles_x = (orig_width + tile_size[0] - 1) // tile_size[0]  # Ceiling division
            n_tiles_y = (orig_height + tile_size[1] - 1) // tile_size[1]  # Ceiling division
            print(f"Number of tiles: {n_tiles_x}x{n_tiles_y}")

            # Get the base name of the input image
            base_name, _ = os.path.splitext(os.path.basename(input_image_path))

            # Split the original image into tiles
            for i in range(n_tiles_x):
                for j in range(n_tiles_y):
                    # Determine tile boundaries, ensuring the last tiles do not exceed the image size
                    x_off = i * tile_size[0]
                    y_off = j * tile_size[1]
                    x_end = min(x_off + tile_size[0], orig_width)
                    y_end = min(y_off + tile_size[1], orig_height)

                    # Crop the tile from the original image
                    tile = src.read(window=((y_off, y_end), (x_off, x_end)))

                    # Define the file path for each tile directly in the output path
                    tile_index = i * n_tiles_y + j  # Unique index for each tile
                    tile_path = os.path.join(output_path, f'{base_name}_out{tile_index}.{output_format}')
                    print(f"Saving tile to: {tile_path}")

                    # Save the tile in the specified format
                    if output_format == 'png':
                        with rasterio.open(tile_path, 'w', driver='PNG', width=tile.shape[2], height=tile.shape[1], count=tile.shape[0], dtype=tile.dtype) as dst:
                            dst.write(tile)
                    elif output_format in ['jpg', 'jpeg']:
                        with rasterio.open(tile_path, 'w', driver='JPEG', width=tile.shape[2], height=tile.shape[1], count=tile.shape[0], dtype=tile.dtype) as dst:
                            dst.write(tile)
                    elif output_format == 'tif':
                        with rasterio.open(tile_path, 'w', driver='GTiff', width=tile.shape[2], height=tile.shape[1], count=tile.shape[0], dtype=tile.dtype) as dst:
                            dst.write(tile)
                    else:
                        print(f"Unsupported output format: {output_format}")
                        return

            print("Image splitting completed and tiles saved successfully.")

    except rasterio.errors.RasterioError as re:
        print(f"Rasterio error occurred: {re}")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 6:
        print("Usage: python split_image.py <input_image_path> <tile_width> <tile_height> <output_path> <output_format>")
        sys.exit(1)

    input_image_path = sys.argv[1]
    tile_size = (int(sys.argv[2]), int(sys.argv[3]))  # Now this will work correctly
    output_path = sys.argv[4]
    output_format = sys.argv[5]  # Capture the output format from command line arguments

    split_image(input_image_path, tile_size, output_path, output_format)