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
 * Last port: geom/PrecisionModel.java r378 (JTS-1.12)
 *
 **********************************************************************/

#include <cmath>
#include <geos/geom/Coordinate.hpp>
#include <geos/geom/PrecisionModel.hpp>
#include <geos/util.hpp>
#include <geos/util/IllegalArgumentException.hpp>
#include <geos/util/math.hpp>
#include <iostream>
#include <sstream>
#include <string>

namespace geos {
namespace geom { // geos::geom

/*public*/
PrecisionModel::PrecisionModel() : modelType(FLOATING), scale(0.0), gridSize(0.0) {
	// modelType=FLOATING;
	// scale=1.0;
}

/*public*/
PrecisionModel::PrecisionModel(Type nModelType) : modelType(nModelType), scale(1.0), gridSize(0.0) {
	// modelType=nModelType;
	// if (modelType==FIXED) setScale(1.0);
	// else setScale(666); // arbitrary number for invariant testing
}

/*public (deprecated) */
PrecisionModel::PrecisionModel(double newScale, double newOffsetX, double newOffsetY) : modelType(FIXED) {
	::geos::ignore_unused_variable_warning(newOffsetX);
	::geos::ignore_unused_variable_warning(newOffsetY);

	// modelType = FIXED;
	setScale(newScale);
}

/*public*/
PrecisionModel::PrecisionModel(double newScale) : modelType(FIXED) {
	setScale(newScale);
}

/*public*/
int PrecisionModel::getMaximumSignificantDigits() const {
	int maxSigDigits = 16;
	if (modelType == FLOATING) {
		maxSigDigits = 16;
	} else if (modelType == FLOATING_SINGLE) {
		maxSigDigits = 6;
	} else if (modelType == FIXED) {

		double dgtsd = std::log(getScale()) / std::log(double(10.0));
		const int dgts = static_cast<int>(dgtsd > 0 ? std::ceil(dgtsd) : std::floor(dgtsd));
		maxSigDigits = dgts;
	}
	return maxSigDigits;
}

/*private*/
void PrecisionModel::setScale(double newScale) {
	/**
	 * A negative scale indicates the grid size is being set.
	 * The scale is set as well, as the reciprocal.
	 */
	if (newScale < 0) {
		gridSize = std::fabs(newScale);
		scale = 1.0 / gridSize;
	} else {
		scale = std::fabs(newScale);
		/**
		 * Leave gridSize as 0, to ensure it is computed using scale
		 */
		gridSize = 0.0;
	}
}

/*public*/
int PrecisionModel::compareTo(const PrecisionModel *other) const {
	int sigDigits = getMaximumSignificantDigits();
	int otherSigDigits = other->getMaximumSignificantDigits();
	return sigDigits < otherSigDigits ? -1 : (sigDigits == otherSigDigits ? 0 : 1);
}

/*public*/
bool PrecisionModel::isFloating() const {
	return (modelType == FLOATING || modelType == FLOATING_SINGLE);
}

/*public*/
double PrecisionModel::makePrecise(double val) const {
	if (modelType == FLOATING_SINGLE) {
		float floatSingleVal = static_cast<float>(val);
		return static_cast<double>(floatSingleVal);
	}
	if (modelType == FIXED) {
		if (gridSize > 0) {
			return util::round(val / gridSize) * gridSize;
		} else {
			return util::round(val * scale) / scale;
		}
	}
	// modelType == FLOATING - no rounding necessary
	return val;
}

} // namespace geom
} // namespace geos
