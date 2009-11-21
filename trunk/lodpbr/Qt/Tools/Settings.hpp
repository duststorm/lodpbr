/*
 * Settings.hpp
 *
 *  Created on: Nov 21, 2009
 *      Author: fmc
 */

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include<QSettings>
#include<QColor>

class Settings {
public:
	Settings();

	virtual ~Settings();

    QColor getBackgroundColor() const
    {
        return mBackgroundColor;
    }

    QColor getBackgroundColorBottom() const
    {
        return mBackgroundColorBottom;
    }

    QColor getBackgroundColorTop() const
    {
        return mBackgroundColorTop;
    }

    QColor getTextColor() const
    {
        return mTextColor;
    }

    void setBackgroundColor(QColor mBackgroundColor)
    {

    	if (mBackgroundColor.black() >= 125)
    		mTextColor = QColor(Qt::lightGray);
    	else
    		mTextColor = QColor(Qt::darkGray);

        this->mBackgroundColor = mBackgroundColor;
    }

    void setBackgroundColorBottom(QColor mBackgroundColorBottom)
    {
        this->mBackgroundColorBottom = mBackgroundColorBottom;
    }

    void setBackgroundColorTop(QColor mBackgroundColorTop)
    {
        this->mBackgroundColorTop = mBackgroundColorTop;
    }

    void setTextColor(QColor mTextColor)
    {
        this->mTextColor = mTextColor;
    }

private:
	QColor mBackgroundColor;
	QColor mBackgroundColorTop;
	QColor mBackgroundColorBottom;

	QColor mTextColor;
};

#endif /* SETTINGS_HPP_ */
