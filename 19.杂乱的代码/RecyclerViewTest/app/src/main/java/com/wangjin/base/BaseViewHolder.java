package com.wangjin.base;

import android.content.Context;
import android.text.util.Linkify;
import android.util.SparseArray;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.squareup.picasso.Picasso;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

public class BaseViewHolder extends RecyclerView.ViewHolder {
    private final SparseArray<View> views;
    private final Context context;
    private View convertView;

    public BaseViewHolder(@NonNull View view, Context context) {
        super(view);
        this.context = context;
        this.views = new SparseArray<View>();
        convertView = view;
    }

    protected <T extends View> T retrieveView(int viewId) {
        View view = views.get(viewId);
        if (view == null) {
            view = convertView.findViewById(viewId);
            views.put(viewId, view);
        }

        return (T) view;
    }

    public BaseViewHolder setText(int viewId, CharSequence value) {
        TextView view = retrieveView(viewId);
        view.setText(value);
        return this;
    }


    public BaseViewHolder setImageUrl(int viewId, String imageUrl) {
        ImageView view = retrieveView(viewId);
        Picasso.get().load(imageUrl).into(view);
        return this;
    }

    public BaseViewHolder setVisible(int viewId, boolean visibile){
        View view = retrieveView(viewId);
        view.setVisibility(visibile ? View.VISIBLE : View.GONE);

        return this;
    }

    public BaseViewHolder linkify(int viewId){
        TextView view = retrieveView(viewId);
        Linkify.addLinks(view, Linkify.ALL);

        return this;
    }


}
