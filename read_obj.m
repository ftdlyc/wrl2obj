function obj = read_obj(path)
% 读取.obj文件,只能处理没有color信息的obj,格式如下
% v xx xx xx
% vn xx xx xx
% f xx xx xx
fp = fopen(path, 'r');
text = textscan(fp, '%s %f %f %f');
fclose(fp);

vertexs = {};
normals = {};
faces = {};
n_vertexs = 0;
n_normals = 0;
n_faces = 0;
[n, ~] = size(text{1});
for i = 1:n
    type = text{1}{i};
    if strcmp('v', type)
        n_vertexs = n_vertexs + 1;
        vertexs{n_vertexs} = [text{2}(i) -text{3}(i) -text{4}(i)];
    elseif strcmp('vn', type)
        n_normals = n_normals + 1;
        normals{n_normals} = [text{2}(i) -text{3}(i) -text{4}(i)];
    elseif strcmp('f', type)
        n_faces = n_faces + 1;
        faces{n_faces} = int32([text{2}(i) text{3}(i) text{4}(i)]);
    end
end
obj.vertexs = reshape(cell2mat(vertexs), 3, n_vertexs);
obj.normals = reshape(cell2mat(normals), 3, n_normals);
obj.faces = reshape(cell2mat(faces), 3, n_faces);
obj.n_vertexs = n_vertexs;
obj.n_normals = n_normals;
obj.n_faces = n_faces;
end
