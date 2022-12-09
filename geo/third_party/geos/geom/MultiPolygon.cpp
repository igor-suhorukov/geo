/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2011 Sandro Santilli <strk@kbt.io>
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: geom/MultiPolygon.java r320 (JTS-1.12)
 *
 **********************************************************************/

#include <algorithm>
#include <cassert>
#include <geos/geom/Geometry.hpp>
#include <geos/geom/LineString.hpp>
#include <geos/geom/MultiPolygon.hpp>
#include <geos/geom/Polygon.hpp>
#include <string>
#include <vector>

namespace geos {
namespace geom { // geos::geom

/*protected*/
MultiPolygon::MultiPolygon(std::vector<Geometry *> *newPolys, const GeometryFactory *factory)
    : GeometryCollection(newPolys, factory) {
}

MultiPolygon::MultiPolygon(std::vector<std::unique_ptr<Polygon>> &&newPolys, const GeometryFactory &factory)
    : GeometryCollection(std::move(newPolys), factory) {
}

MultiPolygon::MultiPolygon(std::vector<std::unique_ptr<Geometry>> &&newPolys, const GeometryFactory &factory)
    : GeometryCollection(std::move(newPolys), factory) {
}

MultiPolygon::~MultiPolygon() {
}

const Polygon *MultiPolygon::getGeometryN(std::size_t i) const {
	return static_cast<const Polygon *>(geometries[i].get());
}

std::string MultiPolygon::getGeometryType() const {
	return "MultiPolygon";
}

GeometryTypeId MultiPolygon::getGeometryTypeId() const {
	return GEOS_MULTIPOLYGON;
}

Dimension::DimensionType MultiPolygon::getDimension() const {
	return Dimension::A; // area
}

} // namespace geom
} // namespace geos
