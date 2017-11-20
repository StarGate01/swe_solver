# Generating And Viewing The Data {#viewpage}

### Required packages:
 - `paraview`
 - It is recommended to download the latest version from https://www.paraview.org/download/

#### SWE1D

Run the program with `../SWE1D` inside the directory `build/data`.

You can of course choose different parameters according to `../SWE1D -h`

Load the state `build/swe1d.pvsm` into paraview, and select `search files under specified directory` in the opening dialog.

The state has one layout with two line charts. The top line chart displays the water height, flux and bathymetry. The bottom line chart displays the froude number.

#### SWE

Run the program with `../SWE_gnu_debug_none_fwave -x 50 -y 50 -o swe` inside the directory `build/data`.

You can of course choose different parameters according to `../SWE_gnu_debug_none_fwave -h`

Load the state `build/swe.pvsm` into paraview, and select `search files under specified directory` in the opening dialog.

The state has two layouts. The first one displays four two-dimensional heightmaps, corresponding to the water height, the fluxes in horizontal and vertical direction, and the bathymetry. The second layout displays a 3D-rendering of the water height and the bathymetry in one.