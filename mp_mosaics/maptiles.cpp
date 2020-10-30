/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    std::map<Point<3>, TileImage*> find;
    std::vector<Point<3>> points;
    for(unsigned i = 0; i<theTiles.size(); i++){
        LUVAPixel curr = theTiles[i].getAverageColor();
        Point<3> point = convertToXYZ(curr);
        points.push_back(point);
        find[point] = &theTiles[i];
    }
    KDTree<3> tree(points);
    int rows = theSource.getRows();
    int cols  = theSource.getColumns();
    MosaicCanvas* canvas = new MosaicCanvas(rows, cols);
    for(int i = 0; i < rows; i++){
        for(int j =0; j<cols; j++){
            LUVAPixel source = theSource.getRegionColor(i, j);
            Point<3> source_point = convertToXYZ(source);
            Point<3> match_point = tree.findNearestNeighbor(source_point);
            TileImage* img = find[match_point];
            canvas->setTile(i, j, img);
        }
    }
    return canvas;
}

