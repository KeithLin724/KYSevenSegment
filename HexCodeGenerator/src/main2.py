'''
Title:Hex code generator
Written By KYLiN
This is a code of mini Hex code generator
for make seven segment code 
only one file to run easy to use 

Date: 29/8/2022
'''

from copy import deepcopy
from tkinter import *
from functools import partial
import logging


class App:
    BNT_HIGHT, BNT_WIDTH = 2, 10
    EMPTY_STR_LIST, STR_LIST = [""] * 7, [chr(97 + i) for i in range(7)]
    DISPLAY = ("left to right", "right to left")

    def __refresh(self):
        """
            refresh the window
        """
        self.__outPutText["state"] = 'normal'

        self.__outPutText.delete(1.0, END)

        tmp = self.__listDisplayHexCode if self.__poseMode == False \
                                        else [elm[::-1] for elm in self.__listDisplayHexCode]

        displayStr = '\n'.join(tmp)
        # logging.info(displayStr)
        self.__outPutText.insert(1.0, displayStr)

        self.__outPutText["state"] = 'disabled'
        logging.info('refresh')
        return

    def __refreshPreView(self):
        self.__preViewText["state"] = 'normal'
        self.__preViewText.delete(1.0, END)
        tmp = self.__hexCodeBuilder if self.__poseMode == False \
                                    else self.__hexCodeBuilder[::-1]

        self.__preViewText.insert(1.0, ''.join(map(str, tmp)))

        self.__preViewText["state"] = 'disabled'
        return

    def __addNumberBnt(self, numberID: int) -> None:
        """_summary_
            add a numberID to the HexBuilder
        Args:
            numberID (int): _description_
        """
        logging.info(f"on click {numberID}")
        self.__hexCodeBuilder[numberID - 1] = int(\
                                                not bool(self.__hexCodeBuilder[numberID - 1]))
        self.__changeButtonColor(numberID=numberID,
                                 colorState=self.__hexCodeBuilder\
                                     [numberID -1])
        self.__refreshPreView()

        logging.info(f"now Build is {self.__hexCodeBuilder}")
        pass

    def __clearNumberHexFunc(self) -> None:
        """_summary_
            clear input 
        """
        self.__hexCodeBuilder = [0] * 8
        for i in range(1, 9):
            self.__changeButtonColor(numberID=i,
                                     colorState=self.__hexCodeBuilder[i - 1])
        self.__refreshPreView()
        logging.info(f"clear Hex func : Now Hex:{self.__hexCodeBuilder}")
        return

    def __addToTotalHexCodeFunc(self) -> None:
        logging.info(f"click")

        tmpStr = ''.join(list(map(str, self.__hexCodeBuilder)))
        self.__listHexCode.append(tmpStr)
        self.__listDisplayHexCode.append(self.__listHexCode[-1])
        logging.debug(f"{self.__listHexCode[-1]}")

        self.__refresh()
        return

    def __clearAllFunc(self) -> None:
        logging.info("clear all")
        self.__listHexCode.clear()
        self.__listDisplayHexCode.clear()

        self.__clearNumberHexFunc()
        self.__refresh()
        self.__refreshPreView()
        return

    def __clearTextBoardFunc(self) -> None:
        """Clear Text Board function"""
        logging.info("clear text board")
        self.__listHexCode.clear()
        self.__listDisplayHexCode.clear()

        self.__refresh()
        return

    def __changeButtonColor(self, numberID: int, colorState: bool) -> None:
        """_summary_

            change the button color using colorState
        Args:
            numberID (int): about the button color 
            colorState (bool): button color state
        """
        if numberID not in self.__buttonDict:
            logging.error("numberID not found in self.__buttonDict")
            return

        self.__buttonDict[numberID]["bg"] = "red" if colorState else "gray"
        pass

    def __showButtonCharFunc(self):
        self.__showState = not self.__showState
        logging.info(f"state {self.__showState}")
        tmpList = App.STR_LIST if self.__showState else App.EMPTY_STR_LIST

        for k in self.__buttonDict.keys():
            if k < 8:
                self.__buttonDict[k]["text"] = deepcopy(tmpList[k - 1])

    def __reverseFunc(self) -> None:
        """_summary_

            reverse the text board function
        """
        logging.info("reverse mode")
        self.__poseMode = not self.__poseMode
        self.__revBnt['text'] = App.DISPLAY[self.__poseMode]
        self.__refreshPreView()
        self.__refresh()
        return

    def __settingLeftUpperFrame(self) -> None:
        upperFrame = Frame(self.__leftFrame)

        labelPre = Label(upperFrame, text="pre-view")
        labelPre.pack(side=LEFT)

        self.__preViewText = Text(upperFrame,
                                  width=10,
                                  height=1,
                                  state="disabled")
        self.__preViewText.pack(side=RIGHT)
        upperFrame.pack()

        self.__showButtonNumber = Button(self.__leftFrame,
                                         text="Show Character",
                                         command=self.__showButtonCharFunc)
        self.__showButtonNumber.pack()
        return

    def __settingSegmentFrame(self) -> None:  # in right
        """_summary_
            about the GUI settings
        """
        self.__mainNumberFrame = Frame(self.__leftFrame, width=400, height=300)

        upperButton = Button(self.__mainNumberFrame,
                             bg="gray",
                             width=App.BNT_WIDTH,
                             height=App.BNT_HIGHT,
                             command=partial(self.__addNumberBnt, 1))

        upperButton.pack()
        self.__buttonDict.update({1: upperButton})

        self.__upperBFrame = Frame(self.__mainNumberFrame)
        upperLeftBnt = Button(self.__upperBFrame,
                              bg="gray",
                              width=App.BNT_WIDTH,
                              height=App.BNT_HIGHT,
                              command=partial(self.__addNumberBnt, 6))

        upperLeftBnt.pack(side=LEFT)
        self.__buttonDict.update({6: upperLeftBnt})

        upperRightBnt = Button(self.__upperBFrame,
                               bg="gray",
                               width=App.BNT_WIDTH,
                               height=App.BNT_HIGHT,
                               command=partial(self.__addNumberBnt, 2))
        upperRightBnt.pack(side=RIGHT)
        self.__buttonDict.update({2: upperRightBnt})

        self.__upperBFrame.pack()

        midButton = Button(self.__mainNumberFrame,
                           bg="gray",
                           width=App.BNT_WIDTH,
                           height=App.BNT_HIGHT,
                           command=partial(self.__addNumberBnt, 7))
        midButton.pack()
        self.__buttonDict.update({7: midButton})

        self.__downBFrame = Frame(self.__mainNumberFrame)
        downLeftBnt = Button(self.__downBFrame,
                             bg="gray",
                             width=App.BNT_WIDTH,
                             height=App.BNT_HIGHT,
                             command=partial(self.__addNumberBnt, 5))

        downLeftBnt.pack(side=LEFT)
        self.__buttonDict.update({5: downLeftBnt})

        downRightBnt = Button(self.__downBFrame,
                              bg="gray",
                              width=App.BNT_WIDTH,
                              height=App.BNT_HIGHT,
                              command=partial(self.__addNumberBnt, 3))
        downRightBnt.pack(side=RIGHT)
        self.__buttonDict.update({3: downRightBnt})

        self.__downBFrame.pack()

        self.__downButtonFrame = Frame(self.__mainNumberFrame)

        downButton = Button(self.__downButtonFrame,
                            bg="gray",
                            width=App.BNT_WIDTH,
                            height=App.BNT_HIGHT,
                            command=partial(self.__addNumberBnt, 4))
        downButton.pack(side=LEFT)
        self.__buttonDict.update({4: downButton})

        dpButton = Button(self.__downButtonFrame,
                          bg="gray",
                          text="DP",
                          width=2,
                          height=2,
                          command=partial(self.__addNumberBnt, 8))
        dpButton.pack(side=RIGHT)
        self.__buttonDict.update({8: dpButton})

        self.__downButtonFrame.pack()
        "--End of Number Frame--"
        self.__mainNumberFrame.pack()

        return

    def __settingNumberControl(self) -> None:
        """_summary_
            setting the Number Control Frame 
        """

        bottomFrame = Frame(self.__leftFrame)

        self.__clearNumberBnt = Button(bottomFrame,
                                       text="Clear",
                                       width=8,
                                       command=self.__clearNumberHexFunc)
        self.__clearNumberBnt.pack(side=LEFT)

        self.__addNumberBnt = Button(bottomFrame,
                                     text="Add",
                                     width=8,
                                     command=self.__addToTotalHexCodeFunc)
        self.__addNumberBnt.pack(side=RIGHT)

        bottomFrame.pack()

        self.__revBnt = Button(self.__leftFrame,
                               text=App.DISPLAY[self.__poseMode],
                               command=self.__reverseFunc)
        self.__revBnt.pack()
        return

    def __settingRightFrame(self) -> None:
        self.__outPutText = Text(self.__rightFrame)
        self.__outPutText.pack()

        bntFrame = Frame(self.__rightFrame)
        self.__clearAllBnt = Button(bntFrame,
                                    text="Clear All",
                                    command=self.__clearAllFunc)
        self.__clearAllBnt.pack(side=LEFT)
        self.__clearTextBoardBnt = Button(bntFrame,
                                          text="Clear Text Board",
                                          command=self.__clearTextBoardFunc)
        self.__clearTextBoardBnt.pack(side=RIGHT)
        bntFrame.pack()

        return

    def __init__(self) -> None:
        FORMAT = "%(asctime)s %(funcName)s: %(message)s"
        logging.basicConfig(level=logging.DEBUG, format=FORMAT)
        "--- Data initialization--"
        self.__listHexCode = []  # original list
        self.__listDisplayHexCode = []  # make some thing and display
        self.__hexCodeBuilder = [0] * 8
        self.__showState = False
        self.__buttonDict = {}
        self.__poseMode = False  # False -> // True <-
        "--End of Data initialization--"
        "----------------------------------------------------------------"
        "---GUI Setting---"
        self.__windows = Tk()
        self.__windows.title("Hex Code Generator")
        "-- Right Frame"
        self.__leftFrame = Frame(self.__windows)
        self.__settingLeftUpperFrame()
        self.__settingSegmentFrame()
        self.__settingNumberControl()
        self.__leftFrame.pack(side=LEFT)
        "--End of Right Frame--"
        "--Left Frame"
        self.__rightFrame = Frame(self.__windows)
        self.__settingRightFrame()
        self.__rightFrame.pack(side=RIGHT)
        "-- End of Left Frame--"
        self.__windows.mainloop()
        "--- End of GUI ---"
        return


if __name__ == '__main__':
    app = App()
