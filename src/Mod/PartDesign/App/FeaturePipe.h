/***************************************************************************
 *   Copyright (c) 2015 Stefan Tröger <stefantroeger@gmx.net>              *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#ifndef PARTDESIGN_Pipe_H
#define PARTDESIGN_Pipe_H

#include <App/PropertyStandard.h>
#include "FeatureSketchBased.h"
#include <BRepOffsetAPI_MakePipeShell.hxx>

namespace PartDesign
{

class PartDesignExport Pipe : public ProfileBased
{
    PROPERTY_HEADER(PartDesign::Pipe);

public:
    Pipe();


    App::PropertyLinkSub     Spine;
    App::PropertyBool        SpineTangent;
    App::PropertyLinkSub     AuxillerySpine;
    App::PropertyBool        AuxillerySpineTangent;
    App::PropertyBool        AuxilleryCurvelinear;
    App::PropertyEnumeration Mode;
    App::PropertyVector      Binormal;
    App::PropertyEnumeration Transition;
    App::PropertyEnumeration Transformation;
    App::PropertyLinkSubList Sections;
    App::PropertyBool        MoveProfile;
    App::PropertyBool        RotateProfile;

    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    void setupObject();
    /// returns the type name of the view provider
    const char* getViewProviderName(void) const {
        return "PartDesignGui::ViewProviderPipe";
    }
    //@}

    static App::DocumentObjectExecReturn *_execute(ProfileBased *feat,
                                                   const TopoShape &path,
                                                   const TopLoc_Location &invObjLoc = TopLoc_Location(),
                                                   int transition = 0,
                                                   const TopoShape &auxpath = TopoShape(),
                                                   bool auxCurveLinear = true,
                                                   int mode = 2,
                                                   const Base::Vector3d &binormalVector = Base::Vector3d(),
                                                   int transformation = 0,
                                                   const std::vector<App::PropertyLinkSubList::SubSet> &multisections = {},
                                                   bool moveProfile = false,
                                                   bool rotateProfile = false);
protected:
    ///get the given edges and all their tangent ones
    void getContinuousEdges(Part::TopoShape TopShape, std::vector< std::string >& SubNames);
    TopoShape buildPipePath(const App::PropertyLinkSub &link, const TopLoc_Location &loc);
    static void setupAlgorithm(BRepOffsetAPI_MakePipeShell& mkPipeShell,
                               int mode,
                               const Base::Vector3d &binormalVector,
                               int transition,
                               const TopoShape& auxshape,
                               bool auxCurveLinear);
    // handle changed property
    virtual void handleChangedPropertyType(Base::XMLReader& reader, const char* TypeName, App::Property* prop);

private:
    static const char* TypeEnums[];
    static const char* TransitionEnums[];
    static const char* ModeEnums[];
    static const char* TransformEnums[];
};

class PartDesignExport AdditivePipe : public Pipe {

    PROPERTY_HEADER(PartDesign::AdditivePipe);
public:
    AdditivePipe();
};

class PartDesignExport SubtractivePipe : public Pipe {

    PROPERTY_HEADER(PartDesign::SubtractivePipe);
public:
    SubtractivePipe();
};

} //namespace PartDesign


#endif // PARTDESIGN_Pipe_H
