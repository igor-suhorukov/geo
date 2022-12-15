/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2013 Sandro Santilli <strk@kbt.io>
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: algorithm/Centroid.java r728 (JTS-0.13+)
 *
 **********************************************************************/

#pragma once

#include <geos/export.hpp>
#include <geos/geom/Coordinate.hpp> // for composition
#include <memory>                   // for std::unique_ptr

// Forward declarations
namespace geos {
namespace geom {
class Geometry;
class Polygon;
class CoordinateSequence;
} // namespace geom
} // namespace geos

namespace geos {
namespace algorithm { // geos::algorithm

/** \brief
 * Computes the centroid of a [Geometry](@ref geom::Geometry) of any dimension.
 *
 * If the geometry is nomimally of higher dimension, but contains only
 * components having a lower effective dimension (i.e. zero length or area),
 * the centroid will be computed appropriately.
 *
 * ### Algorithm #
 *
 * - **Dimension = 2** - Based on the usual algorithm for calculating
 *     the centroid as a weighted sum of the centroids
 *     of a decomposition of the area into (possibly overlapping) triangles.
 *     The algorithm has been extended to handle holes and multi-polygons.
 *     See http://www.faqs.org/faqs/graphics/algorithms-faq/
 *     for further details of the basic approach.
 * - **Dimension = 1** - Computes the average of the midpoints
 *     of all line segments weighted by the segment length.
 * - **Dimension = 0** - Compute the average coordinate over all points.
 *
 * If the input geometries are empty, a `null` Coordinate is returned.
 *
 */
class GEOS_DLL Centroid {
public:
	/** \brief
	 * Computes the centroid point of a geometry.
	 *
	 * @param geom the geometry to use
	 * @param cent will be set to the centroid point, if any
	 *
	 * @return `true` if a centroid could be computed,
	 *         `false` otherwise (empty geom)
	 */
	static bool getCentroid(const geom::Geometry &geom, geom::CoordinateXY &cent);

	/** \brief
	 * Creates a new instance for computing the centroid of a geometry
	 */
	Centroid(const geom::Geometry &geom) : areasum2(0.0), totalLength(0.0), ptCount(0) {
		add(geom);
	}

	/** \brief
	 * Gets the computed centroid.
	 *
	 * @param cent will be set to the centroid point, if any
	 *
	 * @return `true` if a centroid could be computed,
	 *         `false` otherwise (empty geom)
	 */
	bool getCentroid(geom::CoordinateXY &cent) const;

private:
	std::unique_ptr<geom::CoordinateXY> areaBasePt;
	geom::CoordinateXY triangleCent3;
	geom::CoordinateXY cg3;
	geom::CoordinateXY lineCentSum;
	geom::CoordinateXY ptCentSum;
	double areasum2;
	double totalLength;
	int ptCount;

	/**
	 * Adds a Geometry to the centroid total.
	 *
	 * @param geom the geometry to add
	 */
	void add(const geom::Geometry &geom);

	/**
	 * Adds the line segments defined by an array of coordinates
	 * to the linear centroid accumulators.
	 *
	 * @param pts an array of {@link Coordinate}s
	 */
	void addLineSegments(const geom::CoordinateSequence &pts);

	/**
	 * Adds a point to the point centroid accumulator.
	 * @param pt a {@link Coordinate}
	 */
	void addPoint(const geom::CoordinateXY &pt);
};

} // namespace algorithm
} // namespace geos
