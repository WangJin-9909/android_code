package com.example.baidupicn.net;

import java.io.BufferedReader;
import java.io.InputStreamReader;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;

public class HttpUtils {
	/**
	 * 示例：浏览器中输入：http://image.baidu.com/channel/listjson?pn=0&rn=100&tag1=%E7%BE%8E%E5%A5%B3&ftags&sorttype=0&ie=utf8&oe=utf-8&image_id=&tag2=
	 * 服务器返回数据：{"tag1":"美女","tag2":"","totalNum":30000,"start_index" :0,"return_number" :1,"data":[{ "id" :"20905629842","setId" :"167808","pn" :0,"abs":"性感模特徐梦昕美艳嫩胸诱惑","desc" :"性感模特徐梦昕美艳嫩胸诱惑","tags":["大胸"],"tag" :"","date" :"2016-10-25","like_num" :"","is_single" :"", "fashion_id" :"","dress_id" :"","fushi_obj_num" :"","fushi_obj_array": "null","dress_buy_link" : "","dress_price" : "","dress_tag" : "", "dress_num" : "", "dress_discount" : "","dress_other" : "", "dress_extend_type" : "", "dress_extend_name" : "","children_vote" :"","dislike_num" :"","image_url":"http://c.hiphotos.baidu.com/image/pic/item/d009b3de9c82d1585e277e5f840a19d8bd3e42b2.jpg","image_width":700,"image_height":1000, "download_url" :"http://c.hiphotos.baidu.com/image/pic/item/d009b3de9c82d1585e277e5f840a19d8bd3e42b2.jpg","thumbnail_url":"http://c.hiphotos.baidu.com/image/w%3D230/sign=1f8813373d01213fcf3349df64e636f8/d009b3de9c82d1585e277e5f840a19d8bd3e42b2.jpg","thumbnail_width":230,"thumbnail_height":328,"thumb_large_width":310,"thumb_large_height":442,"thumb_large_url":"http://c.hiphotos.baidu.com/image/w%3D310/sign=93712bdf253fb80e0cd167d606d02ffb/d009b3de9c82d1585e277e5f840a19d8bd3e42b2.jpg","site_name":"","site_logo":"","site_url":"http://www.mzitu.com","from_url":"http://www.mzitu.com/9223","obj_url":"http://pic.dofay.com/2013/08/1319412W4-0.jpg", "share_url":"http://c.hiphotos.baidu.com/image/s%3D550%3Bc%3Dwantu%2C8%2C95/sign=d3ac85d4344e251fe6f7e4fd97bdaa2a/d009b3de9c82d1585e277e5f840a19d8bd3e42b2.jpg?referer=6e9b809bd288d43fa9bea5c2ae50","download_num" :0, "collect_num" :0,"start_index" :0,"return_number" :1,"album_di":"","can_album_id":"","album_obj_num":"8", "user_id":"495828387", "app_id":"", "colum": "美女", "photo_id":"20905629842", "is_album":0, "is_vip":0, "from_name":0, "hostname": "www.mzitu.com", "parent_tag": "", "desc_info" : "", "other_urls" : [],"isAdapted" :1 },{}]}
	 *
	 */
	private static final String BASE_URL = "http://image.baidu.com/channel/"
			+ "listjson?pn=0&rn=" + Constant.PAGE_SIZE + "&tag1="
			+ Constant.tag1 + "&ftags="
			+ "&sorttype=0&ie=utf8&oe=utf-8&image_id=&tag2=";
	private static final String BASE_URL_wangJin = "http://192.168.1.104/"
			+ "listjson?pn=0&rn=" + Constant.PAGE_SIZE + "&tag1="
			+ Constant.tag1 + "&ftags="
			+ "&sorttype=0&ie=utf8&oe=utf-8&image_id=&tag2=";

	/**
	 * 从服务器上返回数据
	 */

	public static String getContent(String url) throws Exception {

		StringBuilder sb = new StringBuilder();
		HttpClient client = new DefaultHttpClient();
		HttpParams httpParams = client.getParams();

		HttpConnectionParams.setConnectionTimeout(httpParams, 6000);
		HttpConnectionParams.setSoTimeout(httpParams, 6000);
		HttpResponse response = client.execute(new HttpGet(BASE_URL + url));

		HttpEntity entity = response.getEntity();
		if (entity != null) {
			BufferedReader reader = new BufferedReader(new InputStreamReader(
					entity.getContent(), "UTF-8"), 8192);
			String line = null;
			while ((line = reader.readLine()) != null) {
				sb.append(line + "\n");
			}
			reader.close();

		}
		return sb.toString();

	}
}
