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

#include <cstddef>
#include <geos/export.hpp>

// Forward declarations
namespace geos {
namespace noding {
class SegmentString;
}
} // namespace geos

namespace geos {
namespace noding { // geos.noding

/**
 * \brief
 * Processes possible intersections detected by a Noder.
 *
 * The SegmentIntersector is passed to a Noder.
 * The addIntersections method is called whenever the Noder
 * detects that two SegmentStrings <i>might</i> intersect.
 * This class may be used either to find all intersections, or
 * to detect the presence of an intersection.  In the latter case,
 * Noders may choose to short-circuit their computation by calling the
 * isDone method.
 * This class is an example of the <i>Strategy</i> pattern.
 *
 * @version 1.7
 */
class GEOS_DLL SegmentIntersector {

public:
	/**
	 * This method is called by clients
	 * of the SegmentIntersector interface to process
	 * intersections for two segments of the SegmentStrings
	 * being intersected.
	 */
	virtual void processIntersections(SegmentString *e0, std::size_t segIndex0, SegmentString *e1,
	                                  std::size_t segIndex1) = 0;

	/**
	 * \brief
	 * Reports whether the client of this class
	 * needs to continue testing all intersections in an arrangement.
	 *
	 * @return true if there is not need to continue testing segments
	 *
	 * The default implementation always return false (process all intersections).
	 */
	virtual bool isDone() const {
		return false;
	}

	virtual ~SegmentIntersector() {
	}

protected:
	SegmentIntersector() {
	}
};

/// Temporary typedef for namespace transition
typedef SegmentIntersector nodingSegmentIntersector;

} // namespace noding
} // namespace geos
