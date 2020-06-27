package com.example.wangjin.myapplication;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class Main2Fragment extends Fragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_main, container);
        TextView tv = ((TextView) v.findViewById(R.id.fragment));
        tv.setText("main2Fragment");

        return v;
      //  return inflater.inflate(R.layout.fragment_main, container, false);
    }
}
