/* 
 * Struck: Structured Output Tracking with Kernels
 * 
 * Code to accompany the paper:
 *   Struck: Structured Output Tracking with Kernels
 *   Sam Hare, Amir Saffari, Philip H. S. Torr
 *   International Conference on Computer Vision (ICCV), 2011
 * 
 * Copyright (C) 2011 Sam Hare, Oxford Brookes University, Oxford, UK
 * 
 * This file is part of Struck.
 * 
 * Struck is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Struck is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Struck.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef FEATURES_H
#define FEATURES_H

#include "Sample.h"

#include <Eigen/Core>
#include <vector>

class Features
{
public:
	Features();
		
	//ѧϰ���ߵľ��飬������С���������ó�����������չ��Ч�ʸ�
	inline const Eigen::VectorXd& Eval(const Sample& s) const
	{
		const_cast<Features*>(this)->UpdateFeatureVector(s);
		return m_featVec;
	}
	
	//virtual�ؼ������εģ������������Ĭ��ʵ��
	virtual void Eval(const MultiSample& s, std::vector<Eigen::VectorXd>& featVecs)
	{
		// default implementation
		featVecs.resize(s.GetRects().size());//�Ȱ�vector��ά�����ó�һ����
		for (int i = 0; i < (int)featVecs.size(); ++i)
		{
			//���꣬�Ҿ���Eval���������ǲ��Ǻ�Щ����������������һ�����ð�
			//��������ǵ���sample
			featVecs[i] = Eval(s.GetSample(i));
		}
	}
	
	inline int GetCount() const { return m_featureCount; }

protected:
	
	int m_featureCount;
	Eigen::VectorXd m_featVec;
	
	void SetCount(int c);
	virtual void UpdateFeatureVector(const Sample& s) = 0;//��ͬ�������в�ͬ��ʵ�ַ�ʽ
	
};

#endif