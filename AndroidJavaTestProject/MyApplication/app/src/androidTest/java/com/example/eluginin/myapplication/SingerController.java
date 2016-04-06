package com.example.eluginin.myapplication;

/**
 * Created by eluginin on 07.04.16.
 */
public class SingerController {
    private Singer model;
    private SingerView view;

    public SingerController(Singer model, SingerView view){
        this.model = model;
        this.view = view;
    }

    public void setSingerName(String name){
        model.setName(name);
    }

    public String getSingerName(){
        return model.getName();
    }

    public void setSingerInfo(String info){
        model.setInfo(info);
    }

    public String getSingerInfo(){
        return model.getInfo();
    }

    public void updateView(){
        view.printSingerDetails(model.getName(), model.getInfo());
    }
}
