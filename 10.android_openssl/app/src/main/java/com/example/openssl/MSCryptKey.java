/**
 * @author Dabing
 * @E-mail chenbinging@outlook.com
 * @date 2017-4-12下午3:15:59
 * 非对称密钥
 */
package com.example.openssl;

public class MSCryptKey {

	private int cryptType;
	private String Yz;
	private String Xn;
	private String Ev;
	public MSCryptKey(){
	}
	public MSCryptKey(String Yz, String Xn, String Ev, int type){
		this.cryptType = type;
		this.Yz = Yz;
		this.Xn = Xn;
		this.Ev = Ev;
	}

	public int getCryptType() {
		return cryptType;
	}

	public String getYz() {
		return Yz;
	}

	public String getXn() {
		return Xn;
	}

	public String getEv() {
		return Ev;
	}
}
