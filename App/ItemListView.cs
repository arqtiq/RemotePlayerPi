using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Util;
using Android.Views;
using Android.Widget;

namespace RemotePlayerPiApp
{
    public enum ItemType
    {
        Folder, Song
    }

    public class ItemListView : LinearLayout
    {
        int id;

        public ItemListView(Context context, ItemType type, string title, string desc, int id) :
            base(context)
        {
            Initialize(type, title, desc, id);
        }

        private void Initialize(ItemType type, string title, string desc, int id)
        {
            LayoutInflater inflater = LayoutInflater.FromContext(Context);
            inflater.Inflate(Resource.Layout.item, this);

            //FindViewById<ImageView>(Resource.Id.itemIcon).SetImageURI(Android.Net.Uri.Parse("@android:drawable/ic_media_play"));
            FindViewById<TextView>(Resource.Id.itemTitle).Text = title;
            FindViewById<TextView>(Resource.Id.itemDescription).Text = desc;
        }
    }
}