//Our includes
#include "psSurvex3DParser.h"
#include "psStationLookup.h"
#include "psStation.h"
#include "psLine.h"

//Survex includes
#include <img.h>

//Qt includes
#include <QString>
#include <QDebug>

//Std includes
#include <limits>

psSurvex3DParser::psSurvex3DParser()
{
}

void psSurvex3DParser::parse(QString filename) {
    //Open the survey from the file
    img* survey = img_open_survey((const char*)filename.toAscii(), NULL);
    if(survey == NULL) {
        //Error couldn't open file
        qWarning() << "PlotSauce couldn't open " << filename;
        return;
    }

    float xmin = std::numeric_limits<float>::max();
    float xmax = -std::numeric_limits<float>::max();
    float ymin = std::numeric_limits<float>::max();
    float ymax = -std::numeric_limits<float>::max();
    float zmin = std::numeric_limits<float>::max();
    float zmax = -std::numeric_limits<float>::max();

    float depthmax = -std::numeric_limits<float>::max();
    int datemax = 0;

    int result;
    img_point prev_pt = {0,0,0};
    bool current_polyline_is_surface = false;
    bool pending_move = false;
    // When a traverse is split between surface and underground, we split it
    // into contiguous traverses of each, but we need to track these so we can
    // assign the error statistics to all of them.  So we keep counts of how
    // many surface_traverses and traverses we've generated for the current
    // traverse.
    size_t n_traverses = 0;
    size_t n_surface_traverses = 0;

    psStationLookup stationLookup;
    psStation* previousStation = NULL;
    psStation* currentStation = NULL;

    //Parse that bitch, copied straight out of maintrm.cc for aven
    do {
        img_point pt;
        result = img_read_item(survey, &pt);

        switch (result) {
        case img_MOVE: {
            //Get the current line
            QVector3D position(pt.x, pt.y, pt.z);
            currentStation = stationLookup.findStation(position);
            if(currentStation == NULL) {
                currentStation = new psStation();
                currentStation->setPosition(position);
                stationLookup.addStation(currentStation);
            }

            QString stationName = QString::fromLocal8Bit(survey->label);

            n_traverses = n_surface_traverses = 0;
            pending_move = true;
            prev_pt = pt;
            previousStation = currentStation;
            break;
}
        case img_LINE: {
            QVector3D position(pt.x, pt.y, pt.z);
            currentStation = stationLookup.findStation(position);
            if(currentStation == NULL) {
                currentStation = new psStation();
                currentStation->setPosition(position);
                stationLookup.addStation(currentStation);
            }

            // Update survey extents.
            if (pt.x < xmin) xmin = pt.x;
            if (pt.x > xmax) xmax = pt.x;
            if (pt.y < ymin) ymin = pt.y;
            if (pt.y > ymax) ymax = pt.y;
            if (pt.z < zmin) zmin = pt.z;
            if (pt.z > zmax) zmax = pt.z;

            int date = survey->days1;
            if (date != -1) {
                date += (survey->days2 - date) / 2;
                //if (date < m_DateMin) m_DateMin = date;
                if (date > datemax) datemax = date;
            } else {
                //complete_dateinfo = false;
            }

            bool is_surface = (survey->flags & img_FLAG_SURFACE);
            if (!is_surface) {
                //if (pt.z < m_DepthMin) m_DepthMin = pt.z;
                if (pt.z > depthmax) depthmax = pt.z;
            }
            if (pending_move || current_polyline_is_surface != is_surface) {
//                if (!current_polyline_is_surface && current_traverse) {
//                    //FixLRUD(*current_traverse);
//                }
                current_polyline_is_surface = is_surface;
                // Start new traverse (surface or underground).
                if (is_surface) {
                    //m_HasSurfaceLegs = true;
                    //surface_traverses.push_back(traverse());
                    //current_surface_traverse = &surface_traverses.back();
//                    ++n_surface_traverses;
                } else {
//                    m_HasUndergroundLegs = true;
//                    traverses.push_back(traverse());
//                    current_traverse = &traverses.back();
//                    ++n_traverses;
                    // The previous point was at a surface->ug transition.
//                    if (prev_pt.z < m_DepthMin) m_DepthMin = prev_pt.z;
                    if (prev_pt.z > depthmax) depthmax = prev_pt.z;
                }
                if (pending_move) {
                    // Update survey extents.  We only need to do this if
                    // there's a pending move, since for a surface <->
                    // underground transition, we'll already have handled
                    // this point.
                    if (prev_pt.x < xmin) xmin = prev_pt.x;
                    if (prev_pt.x > xmax) xmax = prev_pt.x;
                    if (prev_pt.y < ymin) ymin = prev_pt.y;
                    if (prev_pt.y > ymax) ymax = prev_pt.y;
                    if (prev_pt.z < zmin) zmin = prev_pt.z;
                    if (prev_pt.z > zmax) zmax = prev_pt.z;
                }

                if (is_surface) {
//                    current_surface_traverse->push_back(PointInfo(prev_pt));
                } else {
//                    current_traverse->push_back(PointInfo(prev_pt));
                }
            }

            if (is_surface) {
//                current_surface_traverse->push_back(PointInfo(pt, date));
            } else {
//                current_traverse->push_back(PointInfo(pt, date));
            }

            //Create a line
            psLine* line = new psLine(previousStation, currentStation);
            Lines.append(line);
            previousStation = currentStation;


            prev_pt = pt;
            pending_move = false;
            break;
        }

        case img_LABEL: {
//            int flags = survey->flags;
//            if (flags & img_SFLAG_ENTRANCE) {
//               flags ^= (img_SFLAG_ENTRANCE | LFLAG_ENTRANCE);
//            }
//            LabelInfo* label = new LabelInfo(pt, wxString(survey->label, wxConvUTF8), flags);
//            if (label->IsEntrance()) {
//                m_NumEntrances++;
//            }
//            if (label->IsFixedPt()) {
//                m_NumFixedPts++;
//            }
//            if (label->IsExportedPt()) {
//                m_NumExportedPts++;
//            }
//            m_Labels.push_back(label);

            QVector3D position(pt.x, pt.y, pt.z);
            QString stationName = QString::fromLocal8Bit(survey->label);
            currentStation = stationLookup.findStation(stationName);

            if(currentStation == NULL) {
                currentStation = new psStation();
                currentStation->setPosition(position);
                currentStation->setName(stationName);
                stationLookup.addStation(currentStation);
            } else {

            }
            break;
        }

        case img_XSECT: {
//            if (!current_tube) {
//                // Start new current_tube.
//                tubes.push_back(vector<XSect>());
//                current_tube = &tubes.back();
//            }

//            // FIXME: avoid linear search...
//            list<LabelInfo*>::const_iterator i = m_Labels.begin();
//            wxString label(survey->label, wxConvUTF8);
//            while (i != m_Labels.end() && (*i)->GetText() != label) ++i;

//            if (i == m_Labels.end()) {
//                // Unattached cross-section - ignore for now.
//                printf("unattached cross-section\n");
//                if (current_tube->size() == 1)
//                    tubes.resize(tubes.size() - 1);
//                current_tube = NULL;
//                break;
//            }

//            int date = survey->days1;
//            if (date != -1) {
//                date += (survey->days2 - date) / 2;
//                if (date < m_DateMin) m_DateMin = date;
//                if (date > datemax) datemax = date;
//            }

//            current_tube->push_back(XSect(**i, date, survey->l, survey->r, survey->u, survey->d));
            break;
        }

        case img_XSECT_END:
            // Finish off current_tube.
            // If there's only one cross-section in the tube, just
            // discard it for now.  FIXME: we should handle this
            // when we come to skinning the tubes.
//            if (current_tube && current_tube->size() == 1)
//                tubes.resize(tubes.size() - 1);
//            current_tube = NULL;
            break;

        case img_ERROR_INFO: {
            if (survey->E == 0.0) {
                // Currently cavern doesn't spot all articulating traverses
                // so we assume that any traverse with no error isn't part
                // of a loop.  FIXME: fix cavern!
                break;
            }
//            m_HasErrorInformation = true;
//            list<traverse>::reverse_iterator t;
//            t = surface_traverses.rbegin();
//            while (n_surface_traverses) {
//                assert(t != surface_traverses.rend());
//                t->n_legs = survey->n_legs;
//                t->length = survey->length;
//                t->E = survey->E;
//                t->H = survey->H;
//                t->V = survey->V;
//                --n_surface_traverses;
//                ++t;
//            }
//            t = traverses.rbegin();
//            while (n_traverses) {
//                assert(t != traverses.rend());
//                t->n_legs = survey->n_legs;
//                t->length = survey->length;
//                t->E = survey->E;
//                t->H = survey->H;
//                t->V = survey->V;
//                --n_traverses;
//                ++t;
//            }
            break;
        }

        case img_BAD: {
//            m_Labels.clear();

//            // FIXME: Do we need to reset all these? - Olly
//            m_NumFixedPts = 0;
//            m_NumExportedPts = 0;
//            m_NumEntrances = 0;
//            m_HasUndergroundLegs = false;
//            m_HasSurfaceLegs = false;

//            img_close(survey);

//            wxString m = wxString::Format(wmsg(img_error()), file.c_str());
//            wxGetApp().ReportError(m);

            return;
        }

        default:
            break;
        }
    } while (result != img_STOP);

    Stations = stationLookup.allStations();

//    //Finished
//    QList<psStation*> stations = stationLookup.allStations();
//    foreach(psStation* station, stations) {
//        qDebug() << "Parsed station:" << station->name() << station->position();
//    }

}


