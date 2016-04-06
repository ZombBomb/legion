package com.example.eluginin.myapplication;

/**
 * Created by eluginin on 07.04.16.
 */
public class MVCPatternDemo {
    public static void main(String[] args) {

        //fetch student record based on his roll no from the database
        Singer model  = retriveSingerFromDatabase();

        //Create a view : to write student details on console
        SingerView view = new SingerView();

        SingerController controller = new SingerController(model, view);

        controller.updateView();

        //update model data
        controller.setSingerName("John");

        controller.updateView();
    }

    private static Singer retriveSingerFromDatabase(){
        Singer singer = new Singer();
        singer.setName("Robert");
        singer.setInfo("10");
        return singer;
    }
}
