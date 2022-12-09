/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2005-2011 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: algorithm/PointLocator.java 95fbe34b (JTS-1.15.2-SNAPSHOT)
 *
 **********************************************************************/

#pragma once

#include <geos/export.hpp>
#include <geos/geom/Location.hpp> // for inlines

// Forward declarations
namespace geos {
namespace geom {
class CoordinateXY;
class Geometry;
class LinearRing;
class LineString;
class Polygon;
class Point;
} // namespace geom
} // namespace geos

namespace geos {
namespace algorithm { // geos::algorithm

/**
 * \class PointLocator
 *
 * \brief
 * Computes the topological relationship (Location)
 * of a single point to a Geometry.
 *
 * The algorithm obeys the SFS boundaryDetermination rule to correctly determine
 * whether the point lies on the boundary or not.
 *
 * Notes:
 *	- instances of this class are not reentrant.
 *	- LinearRing objects do not enclose any area
 *	  (points inside the ring are still in the EXTERIOR of the ring.)
 *
 */
class GEOS_DLL PointLocator {
public:
	PointLocator() {
	}
	~PointLocator() {
	}

	/**
	 * Computes the topological relationship (Location) of a single point
	 * to a Geometry. It handles both single-element and multi-element Geometries.
	 * The algorithm for multi-part Geometriestakes into account the SFS
	 * Boundary Determination rule.
	 *
	 * @return the Location of the point relative to the input Geometry
	 */
	geom::Location locate(const geom::CoordinateXY &p, const geom::Geometry *geom);

private:
	bool isIn; // true if the point lies in or on any Geometry element

	int numBoundaries; // the number of sub-elements whose boundaries the point lies in

	void computeLocation(const geom::CoordinateXY &p, const geom::Geometry *geom);

	void updateLocationInfo(geom::Location loc);
};

} // namespace algorithm
} // namespace geos
