/*
 * contextGraphicView.h
 *
 *  Created on: Oct 8, 2009
 *      Author: fmc
 */


#include <QtGui>

#ifndef CONTEXTGRAPHICVIEW_H_
#define CONTEXTGRAPHICVIEW_H_

class ContextGraphicView : public QGraphicsView
{
public:
	ContextGraphicView()
    {

    }

protected:
    void resizeEvent(QResizeEvent *event) {
        if (scene())
            scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        QGraphicsView::resizeEvent(event);
    }
};

#endif /* CONTEXTGRAPHICVIEW_H_ */


