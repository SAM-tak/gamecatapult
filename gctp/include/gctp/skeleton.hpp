#ifndef _GCTP_SKELETON_HPP_
#define _GCTP_SKELETON_HPP_
#include <gctp/config.hpp>
#ifdef GCTP_ONCE
#pragma once
#endif // GCTP_ONCE
/** @file
 * GameCatapult モデルの骨組み階層構造クラス
 *
 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
 * @date 2004/01/29 18:43:01
 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
 */
#include <gctp/strutumtree.hpp>
#include <gctp/stringmap.hpp>
#include <iosfwd>               // for std::basic_ostream

namespace gctp {

	/** モデルの骨組み階層構造クラス
	 *
	 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
	 * @date 2004/01/29 18:38:41
	 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
	 */
	class Skeleton : public StrutumTree
	{
	public:
		Skeleton() {}
		explicit Skeleton(const StrutumTree &src) : StrutumTree(src) {}

		/// 複製
		void copy(const Skeleton &src);
		/// 融合
		void merge(const Skeleton &src);

		/// ルートノード製作
		void setUp(const Matrix &value = MatrixC(true)) {
			StrutumTree::setUp(value);
		}
		/// ルートノード製作
		void setUp(const char *name, const Matrix &value = MatrixC(true)) {
			StrutumTree::setUp(value);
			if(name && strlen(name)) index[name] = root().get();
		}

		/// 子ノード製作
		NodeType *add(NodeType &parent, const char *name = NULL, const Matrix *_new = 0);
		/// 子ノード製作
		NodeType *add(NodeType &parent, const CStr name, const Matrix *_new = 0);

		/// 名前によるノード検索
		NodeType *get(const char *name) const {
			return index.get(name);
		}
		/// 名前によるノード検索
		NodeType *get(const CStr name) const {
			return index.get(name);
		}
		/// 名前によるノード検索
		NodeType *operator[](const char *name) const {
			return get(name);
		}
		/// 名前によるノード検索
		NodeType *operator[](const CStr name) const {
			return get(name);
		}

		/// ノードから名前を検索
		const char *getName(const NodeType &node) const {
			for(NodeIndex::const_iterator i = index.begin(); i != index.end(); ++i) {
				if(i->second == reinterpret_cast<const void *const>(&node)) return i->first.c_str();
			}
			return 0;
		}

		/// 元スケルトンの内容で上書き
		Skeleton &sync(const Skeleton &src);

		/// 計算済みマトリクスをセット
		Skeleton &setTransform() {
			StrutumTree::setTransform();
			return *this;
		}
		/// 階層をすべて単位行列に
		Skeleton &setIdentity() {
			StrutumTree::setIdentity();
			return *this;
		}

		typedef StringMap<NodeType *> NodeIndex;
		NodeIndex index;

	GCTP_DECLARE_CLASS

	private:
		template<class E, class T>
		class _PrintVisitor {
			std::basic_ostream<E, T> & os_;
			const Skeleton &skel_;
			int indent_;
			bool print_wtm_;
		public:
			_PrintVisitor(std::basic_ostream<E, T> &os, const Skeleton &skel, int indent, bool print_wtm) : os_(os), skel_(skel), indent_(indent), print_wtm_(print_wtm) {}
			bool operator()(const NodeType &n)
			{
				for(int i = 0; i < indent_; i++) os_ << "\t";
				const char *nodename = skel_.getName(n);
				if(nodename) os_ << "nodename : " << nodename << std::endl;
				else os_ << "nodename : NO NAME" << std::endl;
				if(print_wtm_) os_ << *n << endl;
				else os_ << (*n).lcm() << endl;
				indent_++;
				n.visitChildrenConst(*this);
				indent_--;
				return true;
			}
		};

	public:
		/// インデント付きで出力
		template<class E, class T>
		void printIndented(std::basic_ostream<E, T> & os, int indent, bool print_wtm = true) const
		{
			_PrintVisitor<E, T> visitor(os, *this, indent, print_wtm);
			visit(visitor);
		}
		
		/// インデント付きで出力
		template<class E, class T>
		void print(std::basic_ostream<E, T> & os) const
		{
			printIndented<E, T>(os, 0);
		}

		/// インデント付きで出力
		template<class E, class T>
		void printLCM(std::basic_ostream<E, T> & os) const
		{
			printIndented<E, T>(os, 0, false);
		}
	};

	template<class E, class T>
	std::basic_ostream<E, T> &operator<< (std::basic_ostream<E, T> & os, const Skeleton & skl)
	{
		if(!skl.empty()) {
			os << *skl << ";BoneName{";
			for(Skeleton::NodeIndex::const_iterator i = skl.index.begin(); i != skl.index.end(); ++i) {
				os << i->first << ":" << i->second;
			}
			os << "}";
		}
		return os;
	}

 } // namespace gctp

#endif //_GCTP_SKELETON_HPP_