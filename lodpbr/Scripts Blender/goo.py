''' 	This module contains some simple classes to make it easier to program a GUI.
	The main classes are :

	guispace -		collects the values of the OpenGL script window.
	clicktracker -		tracks the left mouse clicks for the tabs class.
	panel -			draws a coloured panel.
	- -			creates a grid of values that can be used for placing buttons, panels etc.
	tabs -			creates a tab widget with a user defined number of tabs.
	sidetabs -		same as above, but the tabs run down the right side instead of the top.
	'''

import Blender
from Blender import BGL, Draw

class GuiSpace:

	'''  Class to find and store the xstart, ystart,width and height values of the OpenGL window in which the script runs.
	If you create an instance at the start of your gui drawing function, then pass the height and width values to
	your major gui elements, the gui will resize automatically when the window resizes.  '''

	def __init__(self, background):

		##   Basic background colour.
		BGL.glClearColor(background[0],background[1],background[2],background[3])

		##   Clear the OpenGL script window to background colour.
		BGL.glClear(BGL.GL_COLOR_BUFFER_BIT)

		##   Create a buffer space for the values we're after.
		scissorbox=BGL.Buffer(BGL.GL_FLOAT,4)

		##   Get the openGL window size values.
		BGL.glGetFloatv(BGL.GL_SCISSOR_BOX,scissorbox)

		##   The scissorbox values are floats, so we change them to integers. This prevents protests from Python about "int expected".
		##   The left and base values are mainly used to calculate the position of the mouse x and y values.

		#  Left side of the OpenGL script window. Value is in pixels, from the left side of the main Blender window.
		self.left=int(scissorbox[0])

		#  Bottom of the OpenGL script window.Value is in pixels, up from the bottom of the main Blender window.
		self.base=int(scissorbox[1])

		#  Width of the OpenGL script window.
		self.width=int(scissorbox[2])

		#  Height of the OpenGL script window.
		self.height=int(scissorbox[3])


class ClickTracker:

	'''    	If you are going to use  tabs in your GUI, you must create one of these. It checks if any leftmouse clicks are on a tab.
		Once it is set up, everything is dealt with automatically, so that you can concentrate on the buttons and sliders.'''

	def __init__(self):

		##   This list that contains the tab panels that are currently on screen.
		self.targets=[]


	def clickcheck(self,x,y):

		##   x and y are the screen coordinates of the mouse at the time of the left mouse click.

		##   Go through our list of targets (tab panels).
		for target in self.targets:

			##   Check the target.box attribute.   Do we have a hit?
			if (y>target.box[0] and y<target.box[1])and(x>target.box[2] and x<target.box[3]):

				##   Is it a sidetabs object? If it is we need to search up and down with the y coordinate.
				if target.orientation:

					along=y

					##   Go through the tabs (target.divs values), locate the one that was clicked on.
					for i in range(len(target.divs)-1):

						##   Found it.
						if along<target.divs[i] and along>target.divs[i+1]:

							##   target.pageid.val is the pageid of the tab. Change it to the current value.
							##   Next time the screen is redrawn, this tab's page will be displayed.
							target.pageid.val=i

				##   It's a normal, horizontal tab panel. Search along the x coordinates.
				else:

					along=x
					##   Go through the tabs (target.divs values), locate the one that was clicked on.
					for i in range(len(target.divs)-1):

						##   Found it.
						if along>target.divs[i] and along<target.divs[i+1]+2:

							##   target.pageid.val is the pageid of the tab. Change it to the current value.
							##   Next time the screen is redrawn, this tab's page will be displayed.
							target.pageid.val=i




class Panel:

	'''   	This class is the basic building block of the tabs, but can also be used on its own -
		I use it to surround related button groups with a different background.
		The corners, sides and caption arguements are optional.  If the corners argument is not entered, the default
		is a square cornered panel. A 1 in the list makes a rounded corner.Different patterns of 1's and 0's in the
		corners list make the different panels that make up the tabs.
		The sides list selectively rubs out border lines.
		The caption arguement takea a list with a string and a colour rgb triplet - e.g ["Print this", [0.0,0.0,0.0]].
		If you name all your colours at the start of your program,  stick in the name - e.g ["Print this", black].'''

	def __init__(self,xstart,ystart,width,height,colour,bordercolour, corners=[0,0,0,0],sides=[0,0,0,0],caption=0):

		##   Most of these should be self explanatory
		self.left=xstart
		self.right=xstart+width
		self.top=ystart+height
		self.base=ystart
		self.width=width
		self.height=height
		self.col=colour
		self.bcol=bordercolour
		self.corners=corners
		self.sides=sides
		self.caption=caption

		##   Draw the main background piece.
		self.drawpanel()

		##   Draw in the corners. Default is square edged.
		self.docorners()

		##   Do we want some of the border lines erased, say for making a tab for a tab panel?
		for test in self.sides:

			##   We do?
			if test:

				##   Rub 'em out.
				self.coversides()

		##   Do we want a label, title, exclamation, proclamation etc. in our panel.
		if self.caption:

			self.text=self.caption[0]
			self.textcolour=self.caption[1]

			##   Start writing.
			self.dotext()

	def drawpanel(self):

		##   Draw the main part of the panel.
		BGL.glColor3f(self.col[0],self.col[1],self.col[2])

		BGL.glRecti(self.left+5,self.base,self.right-5,self.top)			##   Large middle bit.
		BGL.glRecti(self.left,self.base+4,self.left+8,self.top-4)			##   Left small side strip.
		BGL.glRecti(self.right-8,self.base+4,self.right,self.top-4)		##   Right small side strip.

		##   Draw the borders.
		BGL.glColor3f(self.bcol[0],self.bcol[1],self.bcol[2])			##   Change to border colour.

		BGL.glBegin(BGL.GL_LINES)

		BGL.glVertex2i(self.left+6,self.base)						##   Base border.
		BGL.glVertex2i(self.right-6,self.base)

		BGL.glVertex2i(self.left+6,self.top)						##   Top border.
		BGL.glVertex2i(self.right-6,self.top)

		BGL.glVertex2i(self.left,self.base+6)						##   Left border.
		BGL.glVertex2i(self.left,self.top-6)

		BGL.glVertex2i(self.right,self.base+6)						##   Right border.
		BGL.glVertex2i(self.right,self.top-6)

		BGL.glEnd()

	def docorners(self):

		##   Draw the corners.

		if self.corners[0]:										##   Top left corner.
			Corner(self.left,self.top,self.col,self.bcol,1)
		else:
			LCorner(self.left,self.top,self.col,self.bcol,1)

		if self.corners[1]:										##  Top right corner.
			Corner(self.right,self.top,self.col,self.bcol,2)
		else:
			LCorner(self.right,self.top,self.col,self.bcol,2)

		if self.corners[2]:										## Bottom right corner.
			Corner(self.right,self.base,self.col,self.bcol,3)
		else:
			LCorner(self.right,self.base,self.col,self.bcol,3)

		if self.corners[3]:										## Bottom left corner.
			Corner(self.left,self.base,self.col,self.bcol,4)
		else:
			LCorner(self.left,self.base,self.col,self.bcol,4)


	def coversides(self):

		##   This function draws lines to cover up border lines designated by the sides arguement.

		BGL.glColor3f(self.col[0],self.col[1],self.col[2])

		if self.sides[0]:			# left border

			BGL.glBegin(BGL.GL_LINES)

			BGL.glVertex2i(self.left,self.base+1)
			BGL.glVertex2i(self.left,self.top)

			BGL.glEnd()

		if self.sides[1]:			# top border

			BGL.glBegin(BGL.GL_LINES)

			BGL.glVertex2i(self.left+1,self.top)
			BGL.glVertex2i(self.right,self.top)

			BGL.glEnd()

		if self.sides[2]:			# right border

			BGL.glBegin(BGL.GL_LINES)

			BGL.glVertex2i(self.right,self.base+1)
			BGL.glVertex2i(self.right,self.top)

			BGL.glEnd()

		if self.sides[3]:			# base border

			BGL.glBegin(BGL.GL_LINES)

			BGL.glVertex2i(self.left+1,self.base)
			BGL.glVertex2i(self.right,self.base)

			BGL.glEnd()

	def dotext(self):

		##   By default this function prints the desired text, in the desired colour centrally in the panel.
		##   Possibly there will be more options in a leter release.

		##   Find the vertical centreline of the panel.
		centreline=self.left+(self.width/2)

		##   Find the horizontal centreline of the panel and subtract about half the height of the font (roughly).
		textline=self.base+(self.height/2-5)

		##   Find the length of the string that was passed in.
		stringlength=Draw.GetStringWidth(self.text)

		##   Halve it.
		offset=stringlength/2

		##   Calculate the start point for the text.
		titlestart=centreline-offset

		##   Change to the text colour.
		BGL.glColor3f(self.textcolour[0],self.textcolour[1],self.textcolour[2])

		##   Position raster.
		BGL.glRasterPos2i(titlestart,textline)

		##   Print it.
		Draw.Text(self.text)


class ScafFold:

	''' 	Creates an invisible grid,  making it easier to place buttons and panels in groups.
		The grid consists of a list of rows and lists of columns to use as button xstart,ystart coordinates and
		a list that can be used for button height sizes.
		The widths of buttons are given names like "full", "half", "twothird", etc'''

	def __init__(self, xstart, ystart, width, height, numrows,topgap=0,sidegap=0 ):

		self.left=xstart
		self.right=xstart+width
		self.top=ystart+height
		self.base=ystart
		self.width=width+sidegap
		self.height=height+topgap

		##   Gap between the rows.
		self.topgap=topgap

		##   Gap between the columns.
		self.sidegap=sidegap

		##   Number of rows required.
		self.numrows=numrows

		##   Height of a row.
		self.slot=self.height/self.numrows

		##   Height of a button
		self.bheight=[self.slot-self.topgap]

		##   List to contain the y coordinates of the rows
		self.row=[]

		##   Following lists contain the x coordinates for the columns.
		self.col1=[self.left]					##   This is full width.
		self.col2=[]						##   Two columns.
		self.col3=[]						##   Three columns.
		self.col4=[]						##   Four col.....ahhh, you get the idea.
		self.col5=[]
		self.col6=[]

		##   Calculate the y coordinates and fit them into the row list.
		for i in range(0,self.numrows):

			level=self.slot*i
			self.row.append(self.base+level)
			self.bheight.append(level+self.slot-self.topgap)

		##   They go in from bottom to top.
		##   We reverse them to give a more natural top down configuration.
		self.row.reverse()

		##   Sizes of the possible button widths. Given fairly simple names.
		self.full=self.width-self.sidegap
		self.half=self.width/2-self.sidegap

		self.third=self.width/3-self.sidegap
		self.twothird=(self.width/3)*2-self.sidegap

		self.quarter=self.width/4
		self.threequarter=self.quarter*3-self.sidegap

		self.fifth=self.width/5
		self.twofifth=(self.fifth*2)-self.sidegap
		self.threefifth=(self.fifth*3)-self.sidegap
		self.fourfifth=(self.fifth*4)-self.sidegap
		
		self.sixth=self.width/6
		self.fivesixth=(self.sixth*5)-self.sidegap


		##   Fill in those x coordinates.
		for i in range(4):

			self.col4.append(self.left+(self.quarter*i))

		for i in range(5):

			self.col5.append(self.left+(self.fifth*i))

		for i in range(6):

			self.col6.append(self.left+(self.sixth*i))

		## Finish off the button widths, this time shrunk by the gap distance.
		self.quarter=self.quarter-self.sidegap
		self.fifth=self.fifth-self.sidegap
		self.sixth=self.sixth-self.sidegap

		##   And finish off the columns.
		self.col2=[self.left,self.col4[2]]
		self.col3=[self.left,self.col6[2],self.col6[4]]



class Tabs:

	'''  	Class that creates a tabbed panel. You decide the number of tabs, the title labels and
		the colour of each tabpage.'''

	def __init__(self,numtabs,titles,colours,bordercolour,textcolour, pageid):


		##   Number of tabs, titles and colours should be equal
		self.numtabs=numtabs
		self.titles=titles
		self.colours=colours

		##   Border colour and text colour are separate for flexibility.
		self.bordercolour=bordercolour
		self.textcolour=textcolour

		##   This is the current tab, starting at 0, going up to numtabs.
		self.pageid=pageid



	def drawtabs(self,xstart,ystart,width,height,tabheight,clicktrack):

		self.left=xstart
		self.right=xstart+width
		self.top=ystart+height
		self.tabline=self.top-tabheight
		self.base=ystart
		self.tabheight=tabheight
		self.pheight=height-self.tabheight
		self.width=width
		self.height=height

		self.tabwidth=self.width/self.numtabs

		##   Flag to tell clicktrack that these tabs run horizontally.
		self.orientation=0

		##   This will contain the xstart, xend, ystart, yend target coordinates for the clicktrack object.
		self.box=[]

		##   List of the x coordinates of the tab sides.
		self.divs=[self.left]

		##   This panel is the big space, the page where you will put your buttons,sliders and whatnot.
		self.pane=Panel(self.left,self.base,self.width,self.pheight,self.colours[self.pageid.val],self.bordercolour,[0,0,1,1])


		##   Accurate tabwidth, in floating point form/
		wid=1.0/float(self.numtabs)

		##   Create the list of divisions(x coordinates) that delineate the side of each tab.
		for i in range(self.numtabs+1):


			##   We already have the first one, self.left.
			if i==0:

				pass

			##   Extreme right hand side
			elif i==self.numtabs:

				division=self.right

				self.divs.append(division)

			else:

				##   Calculate the tabwidth  accurately using float values, then convert back to integers.
				twidth=int(self.width*wid*i)

				##   Anchor the width value to the left side of the tabpanel.
				division=twidth+self.left

				self.divs.append(division)

		##   Create the tabs and their labels.
		for i in range(self.numtabs):

			##   Width of the tab. There may be slight variations due to int rounding.
			width=self.divs[i+1]-self.divs[i]

			##   This is the active tab, so we draw a tab with the bottom border
			##   missing.  It will join to self.pane seamlessly.
			if self.pageid.val==i:

				Panel(self.divs[i],self.tabline,width,self.tabheight,self.colours[i],self.bordercolour,corners=[1,1,0,0],sides=[0,0,0,1], caption=[self.titles[i],self.textcolour])

			##   This is a background tab.
			else:

				Panel(self.divs[i],self.tabline,width,self.tabheight,self.colours[i],self.bordercolour,corners=[1,1,0,0], caption=[self.titles[i],self.textcolour])

			##   Delineate the upper and lower bounds, extreme left and right of the tabs.
			self.box=[self.tabline-1,self.top,self.divs[0],self.divs[-1]]

			##   Pass the target values to clicktrack.
			clicktrack.targets.append(self)


	##   This function for future use.
	def addtab(self,title,colour):

		self.numtabs=self.numtabs+1
		self.titles.append(title)
		self.colours.append(colour)


class SideTabs(Tabs):

	'''  Pretty much the same as tabs but creates a panel with tabs on the right hand side. '''

	def __init__(self,numtabs,titles,colours,bordercolour,textcolour, pageid):

		Tabs.__init__(self,numtabs,titles,colours,bordercolour,textcolour, pageid)

	def drawtabs(self,xstart,ystart,width,height,tabwidth,clicktrack):

		self.left=xstart
		self.right=xstart+width
		self.top=ystart+height
		self.tabline=self.right-tabwidth
		self.base=ystart
		self.tabwidth=tabwidth
		self.pwidth=width-self.tabwidth
		self.width=width
		self.height=height
		self.tabheight=self.height/self.numtabs

		##   Flag to tell clicktrack that these tabs run vertically.
		self.orientation=1

		##   This will contain the xstart, xend, ystart, yend target coordinates for the clicktrack object.
		self.box=[]


		##   These tabs go up and down, start at the bottom.
		self.divs=[self.base]

		##   Main pane.
		self.pane=Panel(self.left,self.base,self.pwidth,self.height,self.colours[self.pageid.val],self.bordercolour,[1,0,0,1])

		##   Check that the titles aren't too wide for the tabs.
		for text in self.titles:

			##   Length of title string in pixels.
			stringlength=Draw.GetStringWidth(text)

			##   If it's wider than the tabwidth value, widen it to accomodate..
			if stringlength>self.tabwidth:

				self.tabwidth=stringlength+4	
				self.tabline=self.right-self.tabwidth

		##   Mostly the same as tabs from here.
		wid=1.0/float(self.numtabs)

		for i in range(self.numtabs+1):

			if i==0:

				pass

			elif i==self.numtabs:

				division=self.top

				self.divs.append(division)

			else:

				twidth=int(self.height*wid*i)

				division=twidth+self.base

				self.divs.append(division)

		##   The division values run from the bottom up. We want them top down. Sooooo....
		self.divs.reverse()

		for i in range(self.numtabs):

			height=self.divs[i]-self.divs[i+1]

			if self.pageid.val==i:

				Panel(self.tabline,self.divs[i+1],self.tabwidth,height,self.colours[i],self.bordercolour,[0,1,1,0],[1,0,0,0], caption=[self.titles[i],self.textcolour])

			else:

				Panel(self.tabline,self.divs[i+1],self.tabwidth,height,self.colours[i],self.bordercolour,[0,1,1,0], caption=[self.titles[i],self.textcolour])

			self.box=[self.divs[-1],self.divs[0],self.tabline-1,self.right]

			clicktrack.targets.append(self)


class Corner:

	''' 	Draws rounded corners on panels. That's about it really.'''
	def __init__(self,x,y,colour,bordercolour,quadrant):

		self.x=x
		self.y=y
		self.col=colour
		self.bcol=bordercolour


		if quadrant==1:
			self.xflip=1
			self.yflip=-1

		elif quadrant==2:
			self.xflip=-1
			self.yflip=-1

		elif quadrant==3:
			self.xflip=-1
			self.yflip=1

		elif quadrant==4:
			self.xflip=1
			self.yflip=1

		self.drawcorner()

	def drawcorner(self):


		BGL.glBegin(BGL.GL_LINES)

		BGL.glColor3f(self.col[0],self.col[1],self.col[2])

		BGL.glVertex2i(self.x+4*self.xflip,self.y+1*self.yflip)
		BGL.glVertex2i(self.x+8*self.xflip,self.y+1*self.yflip)

		BGL.glVertex2i(self.x+2*self.xflip,self.y+2*self.yflip)
		BGL.glVertex2i(self.x+8*self.xflip,self.y+2*self.yflip)

		BGL.glVertex2i(self.x+1*self.xflip,self.y+3*self.yflip)
		BGL.glVertex2i(self.x+8*self.xflip,self.y+3*self.yflip)

		BGL.glVertex2i(self.x+1*self.xflip,self.y+4*self.yflip)
		BGL.glVertex2i(self.x+8*self.xflip,self.y+4*self.yflip)

		# change colour for border, if needed

		BGL.glColor3f(self.bcol[0],self.bcol[1],self.bcol[2])

		BGL.glVertex2i(self.x+5*self.xflip,self.y)
		BGL.glVertex2i(self.x+8*self.xflip,self.y)

		BGL.glVertex2i(self.x+3*self.xflip,self.y+1*self.yflip)
		BGL.glVertex2i(self.x+5*self.xflip,self.y+1*self.yflip)

		BGL.glVertex2i(self.x+2*self.xflip,self.y+2*self.yflip)
		BGL.glVertex2i(self.x+3*self.xflip,self.y+2*self.yflip)

		BGL.glVertex2i(self.x+1*self.xflip,self.y+3*self.yflip)
		BGL.glVertex2i(self.x+2*self.xflip,self.y+3*self.yflip)

		BGL.glVertex2i(self.x+1*self.xflip,self.y+4*self.yflip)
		BGL.glVertex2i(self.x+2*self.xflip,self.y+4*self.yflip)

		BGL.glVertex2i(self.x,self.y+5*self.yflip)
		BGL.glVertex2i(self.x,self.y+8*self.yflip)

		BGL.glEnd()

class LCorner(Corner):

	''' 	Draws square corners on a panel. The default setting.'''
	def drawcorner(self):

		BGL.glColor3f(self.col[0],self.col[1],self.col[2])

		for i in range(8):
			
			BGL.glBegin(BGL.GL_LINES)
			BGL.glVertex2i(self.x,self.y+i*self.yflip)
			BGL.glVertex2i(self.x+8*self.xflip,self.y+i*self.yflip)

			BGL.glEnd()

		# change colour for border, if needed
		BGL.glColor3f(self.bcol[0],self.bcol[1],self.bcol[2])

		BGL.glBegin(BGL.GL_LINES)

		BGL.glVertex2i(self.x,self.y)
		BGL.glVertex2i(self.x+9*self.xflip,self.y)

		BGL.glVertex2i(self.x,self.y)
		BGL.glVertex2i(self.x,self.y+9*self.yflip)

		BGL.glEnd()

class SCorner(Corner):

	''' A diagonal corner style. Not in use yet, if ever.'''

	def drawcorner(self):


		BGL.glBegin(BGL.GL_LINES)

		BGL.glColor3f(self.col[0],self.col[1],self.col[2])

		BGL.glVertex2i(self.x+4*self.xflip,self.y+1*self.yflip)
		BGL.glVertex2i(self.x+8*self.xflip,self.y+1*self.yflip)

		BGL.glVertex2i(self.x+3*self.xflip,self.y+2*self.yflip)
		BGL.glVertex2i(self.x+8*self.xflip,self.y+2*self.yflip)

		BGL.glVertex2i(self.x+2*self.xflip,self.y+3*self.yflip)
		BGL.glVertex2i(self.x+8*self.xflip,self.y+3*self.yflip)

		BGL.glVertex2i(self.x+1*self.xflip,self.y+4*self.yflip)
		BGL.glVertex2i(self.x+8*self.xflip,self.y+4*self.yflip)

		# change colour for border, if needed

		BGL.glColor3f(self.bcol[0],self.bcol[1],self.bcol[2])

		BGL.glVertex2i(self.x+5*self.xflip,self.y)
		BGL.glVertex2i(self.x+8*self.xflip,self.y)

		BGL.glVertex2i(self.x+5*self.xflip,self.y)
		BGL.glVertex2i(self.x,self.y+5*self.yflip)


		BGL.glVertex2i(self.x,self.y+5*self.yflip)
		BGL.glVertex2i(self.x,self.y+8*self.yflip)

		BGL.glEnd()