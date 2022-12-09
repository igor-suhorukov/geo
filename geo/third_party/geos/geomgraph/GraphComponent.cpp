/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2011 Sandro Santilli <strk@kbt.io>
 * Copyright (C) 2005-2006 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: geomgraph/GraphComponent.java r428 (JTS-1.12+)
 *
 **********************************************************************/

#include <cassert>
#include <geos/geomgraph/GraphComponent.hpp>
#include <geos/geomgraph/Label.hpp>

using namespace geos::geom;

namespace geos {
namespace geomgraph { // geos.geomgraph

GraphComponent::GraphComponent()
    : label(), isInResultVar(false), isCoveredVar(false), isCoveredSetVar(false), isVisitedVar(false) {
}

GraphComponent::GraphComponent(const Label &newLabel)
    : label(newLabel), isInResultVar(false), isCoveredVar(false), isCoveredSetVar(false), isVisitedVar(false) {
}

void GraphComponent::setCovered(bool p_isCovered) {
	isCoveredVar = p_isCovered;
	isCoveredSetVar = true;
}

} // namespace geomgraph
} // namespace geos
