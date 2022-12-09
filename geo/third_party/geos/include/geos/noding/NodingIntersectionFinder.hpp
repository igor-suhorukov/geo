/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2006      Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/

#pragma once

#include <geos/geom/Coordinate.hpp>           // for composition
#include <geos/noding/SegmentIntersector.hpp> // for inheritance
#include <geos/noding/SegmentString.hpp>
#include <vector>

// Forward declarations
namespace geos {
namespace algorithm {
class LineIntersector;
}
namespace noding {
class SegmentString;
}
} // namespace geos

namespace geos {
namespace noding { // geos.noding

/**
 * \brief Finds non-noded intersections in a set of {@link SegmentString}s, if any exist.
 *
 * Non-noded intersections include:
 *
 * - intersections which lie in the interior of a segment
 * - intersections at a vertex in the interior of a SegmentString
 * (e.g. with a segment string endpoint or other interior vertex)
 *
 * @version 1.7
 */
class NodingIntersectionFinder : public SegmentIntersector {
public:
	/** \brief
	 * Creates an intersection finder which finds an interior intersection
	 * if one exists
	 *
	 * @param newLi the LineIntersector to use
	 */
	NodingIntersectionFinder(algorithm::LineIntersector &newLi)
	    : li(newLi), interiorIntersection(geom::Coordinate::getNull()), intersectionCount(0),
	      isCheckEndSegmentsOnly(false), findAllIntersections(false) {
	}

	/** \brief
	 * Tests whether an intersection was found.
	 *
	 * @return true if an intersection was found
	 */
	bool hasIntersection() const {
		return !interiorIntersection.isNull();
	}

	/** \brief
	 * Gets the computed location of the intersection.
	 * Due to round-off, the location may not be exact.
	 *
	 * @return the coordinate for the intersection location
	 */
	const geom::Coordinate &getInteriorIntersection() const {
		return interiorIntersection;
	}

	/** \brief
	 * Gets the endpoints of the intersecting segments.
	 *
	 * @return an array of the segment endpoints (p00, p01, p10, p11)
	 */
	const std::vector<geom::Coordinate> &getIntersectionSegments() const {
		return intSegments;
	}

	/** \brief
	 * This method is called by clients of the SegmentIntersector class to process
	 * intersections for two segments of the [SegmentStrings](@ref SegmentString)
	 * being intersected.
	 *
	 * @note Some clients (such as `MonotoneChains`) may optimize away
	 * this call for segment pairs which they have determined do not intersect
	 * (e.g. by an disjoint envelope test).
	 */
	void processIntersections(SegmentString *e0, std::size_t segIndex0, SegmentString *e1,
	                          std::size_t segIndex1) override;

private:
	algorithm::LineIntersector &li;
	geom::Coordinate interiorIntersection;
	std::size_t intersectionCount;
	bool isCheckEndSegmentsOnly;
	bool findAllIntersections;
	std::vector<geom::Coordinate> intSegments;

	/** \brief
	 * Tests if two vertices with at least one in a segmentString interior
	 * are equal.
	 *
	 * @param p0 a segment vertex
	 * @param p1 a segment vertex
	 * @param isEnd0 true if vertex is a segmentString endpoint
	 * @param isEnd1 true if vertex is a segmentString endpoint
	 * @return true if an intersection is found
	 */
	static bool isInteriorVertexIntersection(const geom::Coordinate &p0, const geom::Coordinate &p1, bool isEnd0,
	                                         bool isEnd1) {
		// Intersections between endpoints are valid nodes, so not reported
		if (isEnd0 && isEnd1) {
			return false;
		}

		if (p0.equals2D(p1)) {
			return true;
		}

		return false;
	};

	/** \brief
	 * Tests if an intersection occurs between a SegmentString interior vertex and another vertex.
	 *
	 * @note intersections between two endpoint vertices are valid noding,
	 * and are not flagged.
	 *
	 * @param p00 a segment vertex
	 * @param p01 a segment vertex
	 * @param p10 a segment vertex
	 * @param p11 a segment vertex
	 * @param isEnd00 true if vertex is a segmentString endpoint
	 * @param isEnd01 true if vertex is a segmentString endpoint
	 * @param isEnd10 true if vertex is a segmentString endpoint
	 * @param isEnd11 true if vertex is a segmentString endpoint
	 * @return true if an intersection is found
	 */
	static bool isInteriorVertexIntersection(const geom::Coordinate &p00, const geom::Coordinate &p01,
	                                         const geom::Coordinate &p10, const geom::Coordinate &p11, bool isEnd00,
	                                         bool isEnd01, bool isEnd10, bool isEnd11) {
		if (isInteriorVertexIntersection(p00, p10, isEnd00, isEnd10)) {
			return true;
		}
		if (isInteriorVertexIntersection(p00, p11, isEnd00, isEnd11)) {
			return true;
		}
		if (isInteriorVertexIntersection(p01, p10, isEnd01, isEnd10)) {
			return true;
		}
		if (isInteriorVertexIntersection(p01, p11, isEnd01, isEnd11)) {
			return true;
		}
		return false;
	};

	/** \brief
	 * Tests whether a segment in a SegmentString is an end segment.
	 * (either the first or last).
	 *
	 * @param segStr a segment string
	 * @param index the index of a segment in the segment string
	 * @return true if the segment is an end segment
	 */
	static bool isEndSegment(const SegmentString *segStr, std::size_t index) {
		if (index == 0) {
			return true;
		}
		if (index >= segStr->size() - 2) {
			return true;
		}
		return false;
	};
};

} // namespace noding
} // namespace geos
